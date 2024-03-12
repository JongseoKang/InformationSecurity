#include "./headers/input.h"

char* getInput(){
    char *str;
    int ch;
    size_t len = 0, size = 4;
    str = malloc(sizeof(char)*size);
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

int main(void){
    char *m;


    printf("%d\n", ' ' == '\0');
    printf("input string : ");
    m = getInput();
    printf("output string : %s\n", m);

    free(m);
    return 0;
}