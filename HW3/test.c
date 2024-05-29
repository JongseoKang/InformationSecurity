#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>

#define HMAC_DIGEST_LENGTH 32 // SHA-256 output length in bytes

void hmac_sha256(const unsigned char *key, int key_len,
                 const unsigned char *message, int message_len,
                 unsigned char *digest) {
    HMAC_CTX *ctx;
    ctx = HMAC_CTX_new();
    HMAC_Init_ex(ctx, key, key_len, EVP_sha256(), NULL);
    HMAC_Update(ctx, message, message_len);
    HMAC_Final(ctx, digest, NULL);
    HMAC_CTX_free(ctx);
}

int hmac_sha256_verify(const unsigned char *key, int key_len,
                       const unsigned char *message, int message_len,
                       const unsigned char *expected_digest) {
    unsigned char digest[HMAC_DIGEST_LENGTH];
    hmac_sha256(key, key_len, message, message_len, digest);

    // Compare computed digest with expected digest
    return memcmp(digest, expected_digest, HMAC_DIGEST_LENGTH) == 0;
}

int main() {
    char *key = "secretkey";
    char *key2 = "publickey";
    const char *message = "Hello, World!";
    unsigned char expected_digest[HMAC_DIGEST_LENGTH];
    unsigned char digest[HMAC_DIGEST_LENGTH];

    // Compute the expected HMAC-SHA256 digest
    hmac_sha256((const unsigned char *)key2, strlen(key2),
                (const unsigned char *)message, strlen(message),
                expected_digest);

    // Verify the HMAC-SHA256
    if (hmac_sha256_verify((const unsigned char *)key, strlen(key),
                            (const unsigned char *)message, strlen(message),
                            expected_digest)) {
        printf("HMAC-SHA256 Verification: Success\n");
    } else {
        printf("HMAC-SHA256 Verification: Failed\n");
    }

    return 0;
}
