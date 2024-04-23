#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>

#define HMAC_DIGEST_LENGTH 32 // SHA-256 output length in bytes
#define AES_BLOCK_SIZE 16
#define BUFFER_SIZE 4096
#define ENC 1130
#define DEC 1131

int mode;
char *key, *in, *out, *tag;

int isArg(char *arg);
int inputCheck(int argc, char **argv);
void sha256HashFile(const char *filename, unsigned char *hash);
int removePadding(unsigned char *buffer, int length);
void decryptFile(const char *inputFilename, const char *outputFilename, const unsigned char *key);
void addPadding(unsigned char *inputBuffer, size_t bytesRead, size_t blockSize);
void encryptFile(const char *inputFilename, const char *outputFilename, const unsigned char *key);
void hmac_sha256(const unsigned char *key, const unsigned char *message, unsigned int message_len, unsigned char *digest);
int hmac_sha256_verify(const unsigned char *key, const unsigned char *message, unsigned int message_len, const unsigned char *expected_digest);
unsigned char *fileReader(const char *fileName, unsigned int *len);
void fileRecorder(const char *fileName, const unsigned char *message, unsigned int len);

int main(int argc, char **argv)
{
    if (inputCheck(argc, argv))
    {
        puts("ERROR");

        free(key);
        free(in);
        free(out);
        free(tag);
        return 2;
    }

    unsigned char hashedKey[SHA256_DIGEST_LENGTH], digest[HMAC_DIGEST_LENGTH];
    unsigned char *tagMessage, *encMessage;
    unsigned int tagMessageLen = 0, encMessageLen = 0;

    if (mode == ENC)
    {
        sha256HashFile(key, hashedKey);
        encryptFile(in, out, hashedKey);
        encMessage = fileReader(out, &encMessageLen);
        hmac_sha256(hashedKey, encMessage, encMessageLen, digest);
        fileRecorder(tag, digest, HMAC_DIGEST_LENGTH);

        free(encMessage);
        free(key);
        free(in);
        free(out);
        free(tag);
        return 0;
    }
    else if (mode == DEC)
    {
        sha256HashFile(key, hashedKey);
        encMessage = fileReader(in, &encMessageLen);
        tagMessage = fileReader(tag, &tagMessageLen);

        if(tagMessageLen == HMAC_DIGEST_LENGTH){
            memcpy(digest, tagMessage, HMAC_DIGEST_LENGTH);
        }
        else{
            puts("VERIFICATION FAILURE");

            free(tagMessage);
            free(encMessage);
            free(key);
            free(in);
            free(out);
            free(tag);
            return 1;
        }


        if (hmac_sha256_verify(hashedKey, encMessage, encMessageLen, digest))
        {
            decryptFile(in, out, hashedKey);

            free(tagMessage);
            free(encMessage);
            free(key);
            free(in);
            free(out);
            free(tag);
            return 0;
        }
        else
        {
            puts("VERIFICATION FAILURE");

            free(tagMessage);
            free(encMessage);
            free(key);
            free(in);
            free(out);
            free(tag);
            return 1;
        }
    }

    return 0;
}

int isArg(char *arg){
    if(strcmp(arg, "-key") == 0) return 1;
    if(strcmp(arg, "-tag") == 0) return 1;
    if(strcmp(arg, "-in") == 0) return 1;
    if(strcmp(arg, "-out") == 0) return 1;

    return 0;
}

int inputCheck(int argc, char **argv)
{
    if (argc != 10)
        return 1;

    int keyCheck, inCheck, outCheck, tagCheck, argnums;
    keyCheck = inCheck = outCheck = tagCheck = argnums = 0;

    if (strcmp(argv[1], "enc") == 0)
        mode = ENC;
    else if(strcmp(argv[1], "dec") == 0)
        mode = DEC;
    else
        return 1;

    for (int i = 2; i < argc; i += 2)
    {
        if (!keyCheck && strcmp(argv[i], "-key") == 0)
        {
            if (isArg(argv[i + 1])) return 1;
            keyCheck++;
            argnums++;
            key = malloc(strlen(argv[i + 1]));
            strcpy(key, argv[i + 1]);
        }
        else if (!inCheck && strcmp(argv[i], "-in") == 0)
        {
            if (isArg(argv[i + 1])) return 1;
            inCheck++;
            argnums++;
            in = malloc(strlen(argv[i + 1]));
            strcpy(in, argv[i + 1]);
        }
        else if (!outCheck && strcmp(argv[i], "-out") == 0)
        {
            if (isArg(argv[i + 1])) return 1;
            outCheck++;
            argnums++;
            out = malloc(strlen(argv[i + 1]));
            strcpy(out, argv[i + 1]);
        }
        else if (!tagCheck && strcmp(argv[i], "-tag") == 0)
        {
            if (isArg(argv[i + 1])) return 1;
            tagCheck++;
            argnums++;
            tag = malloc(strlen(argv[i + 1]));
            strcpy(tag, argv[i + 1]);
        }
        else
            return 1;
    }

    return argnums < 4;
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

int removePadding(unsigned char *buffer, int length)
{
    unsigned char paddingValue = buffer[length - 1];
    return length - paddingValue;
}

void decryptFile(const char *inputFilename, const char *outputFilename, const unsigned char *key)
{
    FILE *inputFile = fopen(inputFilename, "rb");
    FILE *outputFile = fopen(outputFilename, "wb");

    // Initialize AES decryption context
    AES_KEY aesKey;
    if (AES_set_decrypt_key(key, 256, &aesKey) != 0)
    {
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
    while (bytesRead > 0)
    {
        // Decrypt each block
        nextBytes = fread(nextBuffer, 1, AES_BLOCK_SIZE, inputFile);
        AES_decrypt(inputBuffer, outputBuffer, &aesKey);
        if (nextBytes == 0)
            break;
        fwrite(outputBuffer, 1, AES_BLOCK_SIZE, outputFile);
        strcpy(inputBuffer, nextBuffer);
        bytesRead = nextBytes;
    }

    bytesRead = removePadding(outputBuffer, AES_BLOCK_SIZE);
    if (bytesRead)
    {
        fwrite(outputBuffer, 1, bytesRead, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}

void addPadding(unsigned char *inputBuffer, size_t bytesRead, size_t blockSize)
{
    size_t paddingLength = blockSize - (bytesRead % blockSize);
    for (size_t i = 0; i < paddingLength; i++)
    {
        inputBuffer[blockSize - i - 1] = (unsigned char)paddingLength;
    }
}

void encryptFile(const char *inputFilename, const char *outputFilename, const unsigned char *key)
{
    FILE *inputFile = fopen(inputFilename, "rb");
    FILE *outputFile = fopen(outputFilename, "wb");

    // Initialize AES encryption context
    AES_KEY aesKey;
    if (AES_set_encrypt_key(key, 256, &aesKey) != 0)
    {
        perror("AES_set_encrypt_key failed");
        fclose(inputFile);
        fclose(outputFile);
        return;
    }

    unsigned char inputBuffer[AES_BLOCK_SIZE]; // Twice the block size for padding
    unsigned char nextBuffer[AES_BLOCK_SIZE];  // Twice the block size for padding
    unsigned char outputBuffer[AES_BLOCK_SIZE];
    size_t bytesRead, nextBytes;

    bytesRead = fread(inputBuffer, 1, AES_BLOCK_SIZE, inputFile);
    while (bytesRead > 0)
    {
        // Encrypt each block
        nextBytes = fread(nextBuffer, 1, AES_BLOCK_SIZE, inputFile);
        if (nextBytes == 0)
            break;
        AES_encrypt(inputBuffer, outputBuffer, &aesKey);
        fwrite(outputBuffer, 1, AES_BLOCK_SIZE, outputFile);
        strcpy(inputBuffer, nextBuffer);
        bytesRead = nextBytes;
    }

    // Add PKCS#7 padding
    if (bytesRead == AES_BLOCK_SIZE)
    {
        AES_encrypt(inputBuffer, outputBuffer, &aesKey);
        fwrite(outputBuffer, 1, AES_BLOCK_SIZE, outputFile);
    }
    addPadding(inputBuffer, bytesRead, AES_BLOCK_SIZE);
    AES_encrypt(inputBuffer, outputBuffer, &aesKey);
    fwrite(outputBuffer, 1, AES_BLOCK_SIZE, outputFile);

    fclose(inputFile);
    fclose(outputFile);
}

void hmac_sha256(const unsigned char *key, const unsigned char *message, unsigned int message_len, 
                 unsigned char *digest)
{
    HMAC_CTX *ctx;
    int key_len = SHA256_DIGEST_LENGTH;

    ctx = HMAC_CTX_new();
    HMAC_Init_ex(ctx, key, key_len, EVP_sha256(), NULL);
    HMAC_Update(ctx, message, message_len);
    HMAC_Final(ctx, digest, &key_len);
    HMAC_CTX_free(ctx);
}

int hmac_sha256_verify(const unsigned char *key, const unsigned char *message, unsigned int message_len,
                       const unsigned char *expected_digest)
{
    unsigned char digest[HMAC_DIGEST_LENGTH];
    int key_len = SHA256_DIGEST_LENGTH;

    hmac_sha256(key, message, message_len, digest);

    // Compare computed digest with expected digest
    return memcmp(digest, expected_digest, HMAC_DIGEST_LENGTH) == 0;
}

unsigned char *fileReader(const char *fileName, unsigned int *len)
{
    FILE *input = fopen(fileName, "rb");
    unsigned char *message = malloc(0);
    unsigned char buffer[10];
    
    while(fread(buffer, sizeof(unsigned char), 1, input) > 0){
        message = realloc(message, sizeof(char) * ++(*len));
        message[*len - 1] = buffer[0];
    }

    fclose(input);
    return message;
}

void fileRecorder(const char *fileName, const unsigned char *message, unsigned int len)
{
    FILE *output = fopen(fileName, "wb");
    fwrite(message, sizeof(char), len, output);
    fclose(output);
}
