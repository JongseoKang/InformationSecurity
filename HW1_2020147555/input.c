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
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}

char** splitInput(char* rawInput, int* size) {
    int wordArraySize = INITIAL_WORD_ARRAY_SIZE; // 초기 배열 크기
    char** words = (char**)malloc(wordArraySize * sizeof(char*));
    if (words == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    char* token = strtok(input, " "); // 공백을 기준으로 문자열을 자름
    int i = 0;
    while (token != NULL) {
        if (i >= wordArraySize) {
            // 단어 배열의 크기가 부족한 경우, 더 큰 크기의 배열을 할당
            wordArraySize += WORD_ARRAY_SIZE_INCREMENT;
            char** temp = (char**)realloc(words, wordArraySize * sizeof(char*));
            if (temp == NULL) {
                printf("Memory reallocation failed!\n");
                exit(1);
            }
            words = temp;
        }

        words[i] = (char*)malloc((strlen(token) + 1) * sizeof(char));
        if (words[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        strcpy(words[i], token); // 토큰을 배열에 복사
        i++;
        token = strtok(NULL, " ");
    }
    *count = i; // 단어 개수 업데이트

    return words;
}

void freeWords(char** words, int count) {
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void){
    char *m;


    printf("input string : ");
    m = getInput();
    printf("output string : %s\n", m);

    free(m);
    return 0;
}