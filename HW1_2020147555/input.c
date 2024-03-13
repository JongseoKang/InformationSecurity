#include "./headers/input.h"

char* getInput(){
    char *str;
    int ch;
    size_t len = 0, size = 4;
    str = realloc(str, sizeof(char)*size);
    if(!str)return NULL;
    while(EOF!=(ch=fgetc(stdin)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return NULL;
        }
    }
    str[len++]=' ';

    return realloc(str, sizeof(char)*len);
}

char** splitInput(char* rawInput, int* size) {
    int wordArraySize = 0; // 초기 배열 크기

    for(char *it = rawInput; *it != '\0'; it++) wordArraySize += ((*it) == ' ');

    char **words = malloc(wordArraySize * sizeof(char*));

    char *token = strtok(rawInput, " "); // 공백을 기준으로 문자열을 자름
    for(int i = 0; i < wordArraySize; i++){
        words[i] = malloc(SIZE(token) * sizeof(char));
        strcpy(words[i], token); // 토큰을 배열에 복사
        token = strtok(NULL, " ");
    }

    *size = wordArraySize;
    return words;
}

void freeWords(char** words, int size) {
    for (int i = 0; i < size; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void){
    char *m, **words;
    int cnt;


    printf("input string : ");
    m = getInput();
    words = splitInput(m, &cnt);

    for(int i = 0; i < cnt; i++){
        printf("%s\n", words[i]);
    }

    freeWords(words, cnt);
    free(m);
    return 0;
}