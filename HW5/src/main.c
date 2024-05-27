#include <stdio.h>
#include <stdlib.h>

#include "../header/rsa_sign.h"
#include "../header/csi4109.h"

int argParser(int argc, char **argv);

int option;
char *privateKeyPath, *publicKeyPath, *execPath;

int main(int argc, char **argv){
    argParser(argc, argv);

    if (option == 0){       // sign
        RSA *privateKey = loadPrivateKey(privateKeyPath);
        unsigned char *message = (unsigned char*)"Hello, RSA!";
        size_t messageLen = strlen((char*)message);

        unsigned char *signature = NULL;
        size_t signatureLen = 0;
        
        signMessage(privateKey, message, messageLen, &signature, &signatureLen);

        add_section(execPath, signature, signatureLen);
    }
    else{                   // verify
        RSA *publicKey = loadPublicKey(publicKeyPath);
    }
    




    if (verifySignature(publicKey, message, messageLen, signature, signatureLen)) {
        printf("\nSignature is valid.\n");
    } else {
        printf("\nSignature is invalid.\n");
    }


    free(privateKeyPath);
    free(publicKeyPath);
    free(execPath);

    free(signature);
    RSA_free(privateKey);
    RSA_free(publicKey);
    return 0;
}

int argParser(int argc, char **argv){
    privateKeyPath = malloc(0);
    publicKeyPath = malloc(0);
    execPath = malloc(0);

    if(strcmp(argv[1], "sign") == 0){
        option = 0;

        privateKeyPath = realloc(privateKeyPath, strlen(argv[5]) + 1);
        strcpy(privateKeyPath, argv[5]);

        execPath = realloc(execPath, strlen(argv[3]) + 1);
        strcpy(execPath, argv[3]);
    }
    else if(strcmp(argv[1], "verify") == 0){
        option = 1;

        publicKeyPath= realloc(publicKeyPath, strlen(argv[5]) + 1);
        strcpy(publicKeyPath, argv[5]);

        execPath = realloc(execPath, strlen(argv[3]) + 1);
        strcpy(execPath, argv[3]);
    }

    return 1;
}