#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

#define AES_BLOCK_SIZE 16

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

    unsigned char inputBuffer[AES_BLOCK_SIZE];
    unsigned char outputBuffer[AES_BLOCK_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(inputBuffer, 1, AES_BLOCK_SIZE, inputFile)) > 0) {
        // Encrypt each block
        AES_encrypt(inputBuffer, outputBuffer, &aesKey);
        fwrite(outputBuffer, 1, bytesRead, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input_file> <output_file> <key>\n", argv[0]);
        return 1;
    }

    const char *inputFilename = argv[1];
    const char *outputFilename = argv[2];
    const unsigned char *key = (const unsigned char *)argv[3];

    if (strlen((const char *)key) != 32) {
        printf("Key must be 32 bytes (256 bits)\n");
        return 1;
    }

    encryptFile(inputFilename, outputFilename, key);

    printf("Encryption complete.\n");
    return 0;
}
