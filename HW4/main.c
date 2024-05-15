#include "hw4.h"
#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char **argv) {
    if (argc < 2) return -1;

    char *input_filename = argv[1];
    int top_k = 3;

    void *handle = dlopen("libdarknet_predict.so", RTLD_LAZY);
    void (*image_classifier)(char*, int) = (void (*)(char*, int))dlsym(handle, "image_classifier");
    image_classifier(input_filename, top_k);

    dlclose(handle);
    return 0;
}
