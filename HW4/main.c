#define _GNU_SOURCE
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>

#define STACK_SIZE (1024 * 1024)


char *filePath, *mntPath, *topKstring;
unsigned int topK;
void (*image_classifier)(const char *, int);


char childStack[STACK_SIZE];
int child(void *arg);

int main()
{
    FILE *request = fopen("requests.txt", "r");

    void *handle = dlopen("libdarknet_predict.so", RTLD_LAZY);
    printf("%s\n", dlerror());
    image_classifier = (void (*)(const char *, int))dlsym(handle, "image_classifier");

    printf("%s\n", dlerror());
    char *dataLine = malloc(0);
    int buffer;
    unsigned int len = 0;
    while (EOF != (buffer = fgetc(request)))
    {
        dataLine = realloc(dataLine, sizeof(char) * ++len);
        if (buffer == '\n')
        {
            dataLine[len - 1] = '\0';

            filePath = malloc(sizeof(char) * len);
            topKstring = malloc(sizeof(char) * len);
            mntPath = malloc(sizeof(char) * (len + 7));
            int i, j, cnt;

            memcpy(mntPath, "./data/", 7);
            for (i = j = cnt = 0; i < len; i++)
            {
                if (dataLine[i] == ':')
                {
                    cnt++;
                    if (cnt == 1)
                        mntPath[i + 7] = '\0';
                    if (cnt == 2)
                    {
                        filePath[j] = '\0';
                        break;
                    }
                }
                else if(cnt < 1)
                    mntPath[i + 7] = dataLine[i];
                else if(cnt < 2)
                    filePath[j++] = dataLine[i];
            }

            for (cnt = 0, i++; i < len; i++, cnt++)
                topKstring[cnt] = dataLine[i];

            topK = atoi(topKstring);

            // int childPID = clone(child, (void*)(childStack + STACK_SIZE), CLONE_NEWNS | CLONE_NEWNET | SIGCHLD, NULL);

            // waitpid(childPID, NULL, 0);

            image_classifier(filePath,  topK);


            free(filePath); 
            free(mntPath);
            free(topKstring);

            len = 0;
        }
        else
            dataLine[len - 1] = buffer;
    }

    free(dataLine);
    puts("1");

    printf("%s\n", dlerror());
    dlclose(handle);


    puts("2");
    fclose(request);
    puts("3");
    return 0;
}

int child(void *arg){
    // mount(mntPath, "/", "", MS_BIND, 0);
    // FILE *tmp = freopen("temp.txt", "w", stdout);

    printf("%s %s %d\n", mntPath, filePath, topK);
    // image_classifier(filePath, topK);

    // fclose(tmp);
    return 0;
}