#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

#define TOP_SECRET 1
#define SECRET 2
#define CONFIDENTIAL 3
#define UNCLASSIFIED 4
#define NOT_IN_POLICY 0

char *getInput(FILE *fp);
void dropRoot(uid_t uid, gid_t gid);

int main(int argc, char **argv)
{
    register struct passwd *pw;
    register uid_t uid;
    register gid_t gid;

    uid = getuid();
    gid = getgid();
    pw = getpwuid(uid);

    char *op = malloc(strlen(argv[1]) + 1);
    char *fileName = malloc(strlen(argv[2]) + 1);
    char *data = NULL;
    char user[300];
    int userLevel, fileLevel;

    // get user name
    strcpy(user, pw->pw_name);

    // get level of file
    if (strcmp(fileName, "top_secret.data") == NULL)
        fileLevel = TOP_SECRET;
    else if (strcmp(fileName, "secret.data") == NULL)
        fileLevel = SECRET;
    else if (strcmp(fileName, "confidential.data") == NULL)
        fileLevel = CONFIDENTIAL;
    else if (strcmp(fileName, "unclassified.data") == NULL)
        fileLevel = UNCLASSIFIED;

    FILE *macPolicy = fopen("mac.policy", "r");
    char *input = getInput(macPolicy);
    char *name = malloc(strlen(input) + 1);
    char *level = malloc(strlen(input) + 1);
    
    
    // find user's clearance level
    while (strlen(input) > 0) 
    {
        strcpy(name, strtok(input, ':'));
        if (strcmp(name, user) == NULL)
        {
            strcpy(level, strtok(NULL, ':'));
            if (strcmp(level, "TOP_SECRET") == NULL)
                userLevel = TOP_SECRET;
            else if (strcmp(level, "SECRET") == NULL)
                userLevel = SECRET;
            else if (strcmp(level, "CONFIDENTIAL") == NULL)
                userLevel = CONFIDENTIAL;
            else if (strcmp(level, "UNCLASSIFIED") == NULL)
                userLevel = UNCLASSIFIED;
            else
                userLevel = NOT_IN_POLICY;

            break;
        }

        free(input);
        input = getInput(macPolicy);
    }

    free(input);
    free(name);
    free(level);
    fclose(macPolicy);

    if (strcmp(op, "READ") == NULL) { // READ Op
        if (userLevel != NOT_IN_POLICY && userLevel <= fileLevel)
        {
            // print file data
            FILE *file = fopen(fileName, "r");
            char *input = getInput(file);

            while (strlen(input) > 0)
            {
                puts(input);
                free(input);
                input = getInput(file);
            }

            free(input);
            fclose(file);
        }
        else puts("ACCESS DENIED");

        // drop root
        dropRoot(uid, gid);

        // make log file
        FILE *logFile = fopen(strcat(user, ".log"), "a");
        fprintf(logFile, "read %s\n", fileName);
        fclose(logFile);
    }
    else { // WRITE Op
        if(userLevel != NOT_IN_POLICY && userLevel >= fileLevel){
            data = malloc(strlen(argv[3]) + 1);

            FILE *file = fopen(fileName, "a");
            fputs(data, file);

            free(data);
            fclose(file);
        }
        else puts("ACCESS DENIED");

        dropRoot(uid, gid);

        FILE *logFile = fopen(strcat(user, ".log"), "a");
        fprintf(logFile, "write %s\n", fileName);
        fclose(logFile);
    }

    free(op);
    free(fileName);
    return 0;
}

char *getInput(FILE *fp)
{
    char *str;
    int ch;
    size_t len = 0, size = 4;
    str = malloc(sizeof(char) * size);
    if (!str)
        return NULL;
    while (EOF != (ch = fgetc(fp)) && ch != '\n')
    {
        str[len++] = ch;
        if (len == size)
        {
            str = realloc(str, sizeof(char) * (size += 16));
            if (!str)
                return NULL;
        }
    }
    str[len++] = '\0';

    return realloc(str, sizeof(char) * len);
}

void dropRoot(uid_t uid, gid_t gid){
    seteuid(uid);
    setegid(gid);
}