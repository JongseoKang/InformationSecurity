#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SIZE
#define SIZE(str) (strlen((str)) + 1)
#endif
#define STDERR -1

char* getInput();
char** splitInput(char* rawInput, int* size);
void freeWords(char** words, int size);


#endif