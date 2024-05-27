#ifndef _RSA_SIGN_H_
#define _RSA_SIGN_H_

#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>

RSA* loadPrivateKey(const char *privKeyPath);
RSA* loadPublicKey(const char *pubKeyPath);
void signMessage(RSA *rsa, unsigned char *msg, size_t msgLen, unsigned char **sig, size_t *sigLen);
int verifySignature(RSA *rsa, unsigned char *msg, size_t msgLen, unsigned char *sig, size_t sigLen);

#endif