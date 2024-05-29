#include "../header/rsa_sign.h"

/*
int main(int argc, char **argv){
    const char *privateKeyPath = "private_key2.pem";
    const char *publicKeyPath = "public_key.pem";

    RSA *privateKey = loadPrivateKey(privateKeyPath);
    RSA *publicKey = loadPublicKey(publicKeyPath);

    unsigned char *message = (unsigned char*)"Hello, RSA!";
    size_t messageLen = strlen((char*)message);

    unsigned char *signature = NULL;
    size_t signatureLen = 0;

    signMessage(privateKey, message, messageLen, &signature, &signatureLen);

    // printf("Signature (base64): ");
    // BIO *b64 = BIO_new(BIO_f_base64());
    // BIO *bioOut = BIO_new_fp(stdout, BIO_NOCLOSE);
    // b64 = BIO_push(b64, bioOut);
    // BIO_write(b64, signature, signatureLen);
    // BIO_flush(b64);
    // BIO_free_all(b64);

    if (verifySignature(publicKey, message, messageLen, signature, signatureLen)) {
        printf("\nSignature is valid.\n");
    } else {
        printf("\nSignature is invalid.\n");
    }

    free(signature);
    RSA_free(privateKey);
    RSA_free(publicKey);
    return 0;
}

*/

RSA* loadPrivateKey(const char *privKeyPath) {
    FILE *privKeyFile = fopen(privKeyPath, "rb");
    RSA *rsa = PEM_read_RSAPrivateKey(privKeyFile, NULL, NULL, NULL);
    fclose(privKeyFile);
    return rsa;
}

RSA* loadPublicKey(const char *pubKeyPath) {
    FILE *pubKeyFile = fopen(pubKeyPath, "rb");
    RSA *rsa = PEM_read_RSA_PUBKEY(pubKeyFile, NULL, NULL, NULL);
    fclose(pubKeyFile);
    return rsa;
}

void signMessage(RSA *rsa, unsigned char *msg, size_t msgLen, unsigned char **sig, size_t *sigLen) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(msg, msgLen, hash);

    *sig = (unsigned char*) malloc(RSA_size(rsa));
    RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, *sig, (unsigned int*)sigLen, rsa);
}

int verifySignature(RSA *rsa, unsigned char *msg, size_t msgLen, unsigned char *sig, size_t sigLen) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(msg, msgLen, hash);

    if (!RSA_verify(NID_sha256, hash, SHA256_DIGEST_LENGTH, sig, sigLen, rsa)) {
        return 0; // Verification failed
    }
    return 1; // Verification successful
}