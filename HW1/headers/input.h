#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SIZE
#define SIZE(str) (strlen((str)) + 1)
#endif

#define STDERR -1
#define VALID 1
#define INVALID 0

char* getInput();
char* strtokNew(char* string, char* delimiter);
char** splitInput(char* rawInput, int* size);
void freeWords(char** words, int size);

int insertKeyCheck(char** words, int size);
int turnKeyCheck(char** words, int size);
int enterHouseCheck(char** words, int size);
int insideMemebersCheck(char** words, int size);
int changeLocksCheck(char** words, int size);
int leaveHouseCheck(char** words, int size);
int keysNamesCheck(char** words, int size);


#endif