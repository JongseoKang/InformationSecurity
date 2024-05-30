#include <stdio.h>
#include <stdlib.h>

#include "../header/rsa_sign.h"
#include "../header/csi4109.h"
#include "../header/elf_parser.h"

int argParser(int argc, char **argv);

int option;
char *privateKeyPath, *publicKeyPath, *execPath;

int main(int argc, char **argv){
    if(argParser(argc, argv)) return 0;

    if (option == 0){       // sign
        RSA *privateKey = loadPrivateKey(privateKeyPath);
        unsigned char *execMsg, *signMsg;
        size_t execSize = 0, signSize = 0;

        execMsg = parseExecScn(execPath, &execSize);
        signMessage(privateKey, execMsg, execSize, &signMsg, &signSize);

        add_section(execPath, signMsg, signSize);

        free(execMsg);
        free(signMsg);
        free(execPath);
        free(privateKeyPath);
        RSA_free(privateKey);
    }
    else{                   // verify
        RSA *publicKey = loadPublicKey(publicKeyPath);
        unsigned char *execMsg, *signMsg;
        size_t execSize = 0, signSize = 0;

        execMsg = parseExecScn(execPath, &execSize);
        signMsg = parseSignScn(execPath, &signSize);

        if(signSize == -1){
            puts("NOT_SIGNED");
        }
        else if(signSize == 256 && verifySignature(publicKey, execMsg, execSize, signMsg, signSize)){
            puts("OK");
        }
        else{
            puts("NOT_OK");
        }

        free(signMsg);
        free(execMsg);
        free(execPath);
        free(publicKeyPath);
        RSA_free(publicKey);
    }
    
    return 0;
}

int argParser(int argc, char **argv){
    if(strcmp(argv[1], "sign") == 0){
        option = 0;

        privateKeyPath = malloc(strlen(argv[5]) + 1);
        strcpy(privateKeyPath, argv[5]);

        execPath = malloc(strlen(argv[3]) + 1);
        strcpy(execPath, argv[3]);

        return 0;
    }
    else if(strcmp(argv[1], "verify") == 0){
        option = 1;

        publicKeyPath= malloc(strlen(argv[5]) + 1);
        strcpy(publicKeyPath, argv[5]);

        execPath = malloc(strlen(argv[3]) + 1);
        strcpy(execPath, argv[3]);

        return 0;
    }

    return 1;
}