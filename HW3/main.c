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

int inputCheck(int agrc, char **agrv);
void sha256HashFile(const char *filename, unsigned char *hash);
void decryptFile(const char *inputFilename, const char *outputFilename, const unsigned char *key);
void encryptFile(const char *inputFilename, const char *outputFilename, const unsigned char *key);

int main(int argc, char **argv)
{
    if (inputCheck(agrc, agrv))
    {
        printf("ERROR\n");

        free(key);
        free(tag);
        return 2;
    }

    if(mode == ENC){

    }
    else if(mode == DEC){

    }



    return 0;
}

int inputCheck(int agrc, char **agrv)
{
    if (agrc & 1)
        return 1;

    // for safe realloc()
    char *buffer;

    int keyCheck, inCheck, outCheck, tagCheck;
    keyCheck = inCheck = outCheck = tagCheck = 0;

    key = malloc(strlen("shared.key"));
    strcpy(key, "shared.key");
    tag = malloc(strlen("encrypted.tag"));
    strcpy(tag, "encrypted.tag");

    if (strcmp(agrv[1], "enc") == 0)
    { // encode mode
        mode = ENC;
        in = malloc(strlen("original.txt"));
        strcpy(in, "original.txt");
        out = malloc(strlen("encrypted.txt"));
        strcpy(out, "encrypted.txt");
    }
    else if (strcmp(agrv[1], "dec") == 0)
    { // decode mode
        mode = DEC;
        in = malloc(strlen("encrypted.txt"));
        strcpy(in, "encrypted.txt");
        out = malloc(strlen("decrypted.txt"));
        strcpy(out, "decrypted.txt");
    }
    else
        return 1;


    for (int i = 2; i < agrc; i += 2)
    {
        if (!keyCheck && strcmp(agrv[i], "key") == 0)
        {
            keyCheck++;
            buffer = key;
            if (NULL == (key = realloc(key, strlen(agrv[i + 1]))))
                free(buffer);
            strcpy(key, agrv[i + 1]);
        }
        else if (!inCheck && strcmp(agrv[i], "in") == 0)
        {
            inCheck++;
            buffer = in;
            if (NULL == (in = realloc(in, strlen(agrv[i + 1]))))
                free(buffer);

            strcpy(in, agrv[i + 1]);
        }
        else if (!outCheck && strcmp(agrv[i], "out") == 0)
        {
            outCheck++;
            buffer = out;
            if (NULL == (out = realloc(out, strlen(agrv[i + 1]))))
                free(buffer);

            strcpy(out, agrv[i + 1]);
        }
        else if (!tagCheck && strcmp(agrv[i], "tag") == 0)
        {
            tagCheck++;
            buffer = tag;
            if (NULL == (tag = realloc(tag, strlen(agrv[i + 1]))))
                free(buffer);

            strcpy(tag, agrv[i + 1]);
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

void decryptFile(const char *inputFilename, const char *outputFilename, const unsigned char *key)
{
    FILE *inputFile = fopen(inputFilename, "rb");
    FILE *outputFile = fopen(outputFilename, "wb");

    if (!inputFile || !outputFile)
    {
        perror("Error opening files");
        return;
    }

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
    unsigned char outputBuffer[AES_BLOCK_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(inputBuffer, 1, AES_BLOCK_SIZE, inputFile)) > 0)
    {
        // Decrypt each block
        AES_decrypt(inputBuffer, outputBuffer, &aesKey);
        fwrite(outputBuffer, 1, bytesRead, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}

void encryptFile(const char *inputFilename, const char *outputFilename, const unsigned char *key)
{
    FILE *inputFile = fopen(inputFilename, "rb");
    FILE *outputFile = fopen(outputFilename, "wb");

    if (!inputFile || !outputFile)
    {
        perror("Error opening files");
        return;
    }

    // Initialize AES encryption context
    AES_KEY aesKey;
    if (AES_set_encrypt_key(key, 256, &aesKey) != 0)
    {
        perror("AES_set_encrypt_key failed");
        fclose(inputFile);
        fclose(outputFile);
        return;
    }

    unsigned char inputBuffer[AES_BLOCK_SIZE];
    unsigned char outputBuffer[AES_BLOCK_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(inputBuffer, 1, AES_BLOCK_SIZE, inputFile)) > 0)
    {
        // Encrypt each block
        AES_encrypt(inputBuffer, outputBuffer, &aesKey);
        fwrite(outputBuffer, 1, bytesRead, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}