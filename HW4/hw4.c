#include "hw4.h"
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2) return -1;

    char *input_filename = argv[1];
    int top_k = 3;

    image_classifier(input_filename, top_k);

    return 0;
}
