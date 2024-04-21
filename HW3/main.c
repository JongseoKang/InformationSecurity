#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/sha.h>

#define AES_BLOCK_SIZE 16
#define BUFFER_SIZE 4096
#define ENC 1130
#define DEC 1131

int mode;
char *key, *in, *out, *tag;

int inputCheck(int argc, char **argv);
void sha256HashFile(const char *filename, unsigned char *hash);
int removePadding(unsigned char *buffer, int length);
void decryptFile(const char *inputFilename, const char *outputFilename, const unsigned char *key);
void addPadding(unsigned char *inputBuffer, size_t bytesRead, size_t blockSize);
void encryptFile(const char *inputFilename, const char *outputFilename, const unsigned char *key);

int main(int argc, char **argv)
{
    if (inputCheck(argc, argv))
    {
        printf("ERROR\n");

        free(key);
        free(in);
        free(out);
        free(tag);
        return 2;
    }

    char hashedKey[SHA256_DIGEST_LENGTH];

    if(mode == ENC){
        sha256HashFile(key, hashedKey);
        encryptFile(in, out, hashedKey);
    }
    else if(mode == DEC){
        sha256HashFile(key, hashedKey);
        decryptFile(in, out, hashedKey);
    }



    free(key);
    free(in);
    free(out);
    free(tag);
    return 0;
}

int inputCheck(int argc, char **argv)
{
    if (argc & 1)
        return 1;

    // for safe realloc()
    char *buffer;

    int keyCheck, inCheck, outCheck, tagCheck;
    keyCheck = inCheck = outCheck = tagCheck = 0;

    key = malloc(strlen("shared.key"));
    strcpy(key, "shared.key");
    tag = malloc(strlen("encrypted.tag"));
    strcpy(tag, "encrypted.tag");

    if (strcmp(argv[1], "enc") == 0)
    { // encode mode
        mode = ENC;
        in = malloc(strlen("original.txt"));
        strcpy(in, "original.txt");
        out = malloc(strlen("encrypted.txt"));
        strcpy(out, "encrypted.txt");
    }
    else if (strcmp(argv[1], "dec") == 0)
    { // decode mode
        mode = DEC;
        in = malloc(strlen("encrypted.txt"));
        strcpy(in, "encrypted.txt");
        out = malloc(strlen("decrypted.txt"));
        strcpy(out, "decrypted.txt");
    }
    else
        return 1;


    for (int i = 2; i < argc; i += 2)
    {
        if (!keyCheck && strcmp(argv[i], "-key") == 0)
        {
            keyCheck++;
            buffer = key;
            if (NULL == (key = realloc(key, strlen(argv[i + 1]))))
                free(buffer);
            strcpy(key, argv[i + 1]);
        }
        else if (!inCheck && strcmp(argv[i], "-in") == 0)
        {
            inCheck++;
            buffer = in;
            if (NULL == (in = realloc(in, strlen(argv[i + 1]))))
                free(buffer);

            strcpy(in, argv[i + 1]);
        }
        else if (!outCheck && strcmp(argv[i], "-out") == 0)
        {
            outCheck++;
            buffer = out;
            if (NULL == (out = realloc(out, strlen(argv[i + 1]))))
                free(buffer);

            strcpy(out, argv[i + 1]);
        }
        else if (!tagCheck && strcmp(argv[i], "-tag") == 0)
        {
            tagCheck++;
            buffer = tag;
            if (NULL == (tag = realloc(tag, strlen(argv[i + 1]))))
                free(buffer);

            strcpy(tag, argv[i + 1]);
        }
        else
            return 1;
    }

    return 0;
}

void sha256HashFile(const char *filename, unsigned char *hash)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    SHA256_CTX sha256Context;
    SHA256_Init(&sha256Context);

    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
    {
        SHA256_Update(&sha256Context, buffer, bytesRead);
    }

    SHA256_Final(hash, &sha256Context);

    fclose(file);
}


int removePadding(unsigned char *buffer, int length) {
    unsigned char paddingValue = buffer[length - 1];
    return length - paddingValue;
}

void decryptFile(const char *inputFilename, const char *outputFilename, const unsigned char *key) {
    FILE *inputFile = fopen(inputFilename, "rb");
    FILE *outputFile = fopen(outputFilename, "wb");

    if (!inputFile || !outputFile) {
        perror("Error opening files");
        return;
    }

    // Initialize AES decryption context
    AES_KEY aesKey;
    if (AES_set_decrypt_key(key, 256, &aesKey) != 0) {
        perror("AES_set_decrypt_key failed");
        fclose(inputFile);
        fclose(outputFile);
        return;
    }

    unsigned char inputBuffer[AES_BLOCK_SIZE];
    unsigned char nextBuffer[AES_BLOCK_SIZE];
    unsigned char outputBuffer[AES_BLOCK_SIZE];
    size_t bytesRead, nextBytes;


    bytesRead = fread(inputBuffer, 1, AES_BLOCK_SIZE, inputFile);
    while (bytesRead > 0) {
        // Decrypt each block
        nextBytes = fread(nextBuffer, 1, AES_BLOCK_SIZE, inputFile);
        AES_decrypt(inputBuffer, outputBuffer, &aesKey);
        if(nextBytes == 0) break;
        fwrite(outputBuffer, 1, AES_BLOCK_SIZE, outputFile);
        strcpy(inputBuffer, nextBuffer);
        bytesRead = nextBytes;
    }

    bytesRead = removePadding(outputBuffer, AES_BLOCK_SIZE);
    if(bytesRead){
        fwrite(outputBuffer, 1, bytesRead, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}

void addPadding(unsigned char *inputBuffer, size_t bytesRead, size_t blockSize) {
    size_t paddingLength = blockSize - (bytesRead % blockSize);
    for (size_t i = 0; i < paddingLength; i++) {
        inputBuffer[blockSize - i - 1] = (unsigned char)paddingLength;
    }
}

void encryptFile(const char *inputFilename, const char *outputFilename, const unsigned char *key) {
    FILE *inputFile = fopen(inputFilename, "rb");
    FILE *outputFile = fopen(outputFilename, "wb");

    if (!inputFile || !outputFile) {
        perror("Error opening files");
        return;
    }

    // Initialize AES encryption context
    AES_KEY aesKey;
    if (AES_set_encrypt_key(key, 256, &aesKey) != 0) {
        perror("AES_set_encrypt_key failed");
        fclose(inputFile);
        fclose(outputFile);
        return;
    }

    unsigned char inputBuffer[AES_BLOCK_SIZE]; // Twice the block size for padding
    unsigned char nextBuffer[AES_BLOCK_SIZE]; // Twice the block size for padding
    unsigned char outputBuffer[AES_BLOCK_SIZE];
    size_t bytesRead, nextBytes;

    bytesRead = fread(inputBuffer, 1, AES_BLOCK_SIZE, inputFile);
    while (bytesRead > 0) {
        // Encrypt each block
        nextBytes = fread(nextBuffer, 1, AES_BLOCK_SIZE, inputFile);
        if(nextBytes == 0) break;
        AES_encrypt(inputBuffer, outputBuffer, &aesKey);
        fwrite(outputBuffer, 1, AES_BLOCK_SIZE, outputFile);
        strcpy(inputBuffer, nextBuffer);
        bytesRead = nextBytes;
    }

    // Add PKCS#7 padding
    addPadding(inputBuffer, bytesRead, AES_BLOCK_SIZE);
    AES_encrypt(inputBuffer, outputBuffer, &aesKey);
    fwrite(outputBuffer, 1, AES_BLOCK_SIZE, outputFile);

    fclose(inputFile);
    fclose(outputFile);
}