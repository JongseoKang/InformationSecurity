#include "./headers/input.h"

char *getInput()
{
    char *str;
    int ch;
    size_t len = 0, size = 4;
    str = realloc(str, sizeof(char) * size);
    if (!str)
        return NULL;
    while (EOF != (ch = fgetc(stdin)) && ch != '\n')
    {
        str[len++] = ch;
        if (len == size)
        {
            str = realloc(str, sizeof(char) * (size += 16));
            if (!str)
                return NULL;
        }
    }
    str[len++] = ' ';

    return realloc(str, sizeof(char) * len);
}

char *strtokNew(char* string, char* delimiter){
    static char *source = NULL;
    char *p, *riturn = 0;
    if (string != NULL)
        source = string;
    if (source == NULL)
        return NULL;

    if ((p = strpbrk(source, delimiter)) != NULL)
    {
        *p = 0;
        riturn = source;
        source = ++p;
    }
    return riturn;
}

char **splitInput(char *rawInput, int *size)
{
    int wordArraySize = 0; // 초기 배열 크기

    for (char *it = rawInput; *it != '\0'; it++)
        wordArraySize += ((*it) == ' ');

    char **words = malloc(wordArraySize * sizeof(char *));

    char *token = strtokNew(rawInput, " "); // 공백을 기준으로 문자열을 자름
    for (int i = 0; i < wordArraySize; i++)
    {
        words[i] = malloc(SIZE(token) * sizeof(char));
        strcpy(words[i], token); // 토큰을 배열에 복사
        token = strtokNew(NULL, " ");
    }

    *size = wordArraySize;
    return words;
}

void freeWords(char **words, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(words[i]);
    }
    free(words);
}


int insertKeyCheck(char** words, int size){
    if(size != 4) return INVALID;
    if(strcmp(words[0], "INSERT")) return INVALID;
    if(strcmp(words[1], "KEY")) return INVALID;
    if(strlen(words[2]) == 0) return INVALID;
    if(strlen(words[3]) == 0) return INVALID;

    return VALID;
}

int turnKeyCheck(char** words, int size){
    if(size != 3) return INVALID;
    if(strcmp(words[0], "TURN")) return INVALID;
    if(strcmp(words[1], "KEY")) return INVALID;
    if(strlen(words[2]) == 0) return INVALID;

    return VALID;
}

int enterHouseCheck(char** words, int size){
    if(size != 3) return INVALID;
    if(strcmp(words[0], "ENTER")) return INVALID;
    if(strcmp(words[1], "HOUSE")) return INVALID;
    if(strlen(words[2]) == 0) return INVALID;

    return VALID;
}

int insideMemebersCheck(char** words, int size){
    if(size != 2) return INVALID;
    if(strcmp(words[0], "WHO\'S")) return INVALID;
    if(strcmp(words[1], "INSIDE?")) return INVALID;

    return VALID;
}

int changeLocksCheck(char** words, int size){
    if(size < 2) return INVALID;
    if(strcmp(words[0], "CHANGE")) return INVALID;
    if(strcmp(words[1], "LOCKS")) return INVALID;

    for(int i = 2; i < size; i++){
        if(strlen(words[i]) == 0) return INVALID;
    }

    return VALID;
}

int leaveHouseCheck(char** words, int size){
    if(size != 3) return INVALID;
    if(strcmp(words[0], "LEAVE")) return INVALID;
    if(strcmp(words[1], "HOUSE")) return INVALID;
    if(strlen(words[2]) == 0) return INVALID;

    return VALID;
}

int keysNamesCheck(char** words, int size){
    for(int i = 2; i < size; i++){
        for(int j = 0; j < strlen(words[i]); j++){
            if(words[i][j] == '-') continue;
            else if(words[i][j] == '_') continue;
            else if(words[i][j] >= 'a' && words[i][j] <= 'z') continue;
            else if(words[i][j] >= 'A' && words[i][j] <= 'Z') continue;
            else if(words[i][j] >= '0' && words[i][j] <= '9') continue;
            else return INVALID;
        }
    }
    
    return VALID;
}