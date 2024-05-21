#define _GNU_SOURCE
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/prctl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <signal.h>
#include <sched.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <errno.h>
#include <seccomp.h>


#define STACK_SIZE (1024 * 1024)


char *filePath, *topKstring;
unsigned int topK;

char childStack[STACK_SIZE];

void (*image_classifier)(const char *, int);
void sandbox();
void makeResult();
void readTemp(const char *dataLine);
int child(void *arg);

int main()
{
    makeResult();
    
    FILE *request = fopen("requests.txt", "r");

    void *handle = dlopen("./libdarknet_predict.so", RTLD_LAZY);
    image_classifier = (void (*)(const char *, int))dlsym(handle, "image_classifier");

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
            int i, cnt;

            memcpy(filePath, "./data/", 7);
            for (i = cnt = 0; i < len; i++)
            {
                if (dataLine[i] == ':')
                {
                    cnt++;
                    if (cnt == 1)
                        filePath[i + 7] = '/';
                    if (cnt == 2)
                    {
                        filePath[i + 7] = '\0';
                        break;
                    }
                }
                else
                    filePath[i + 7]= dataLine[i];
            }

            for (cnt = 0, i++; i < len; i++, cnt++)
                topKstring[cnt] = dataLine[i];

            topK = atoi(topKstring);

            int childPID = clone(child, (void*)(childStack + STACK_SIZE), CLONE_NEWUSER | CLONE_NEWNS | CLONE_NEWNET | SIGCHLD, NULL);

            waitpid(childPID, NULL, 0);


            readTemp(dataLine);

            free(filePath); 
            free(topKstring);

            len = 0;
        }
        else
            dataLine[len - 1] = buffer;
    }


    free(dataLine);
    fclose(request);
    return 0;
}

void sandbox() {
  scmp_filter_ctx ctx;
  ctx = seccomp_init(SCMP_ACT_ALLOW);
  
  if (ctx == NULL) {
    printf("seccomp error\n");
    exit(0);
  }

  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(rt_sigreturn), 0);
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(exit), 0);
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(exit_group), 0);
//   seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(openat), 0);
//   seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 1, SCMP_A0(SCMP_CMP_EQ, open("imagenet.shortnames.list", O_RDONLY)));
//   seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 1, SCMP_A0(SCMP_CMP_EQ, open("darknet.weights", O_RDONLY)));
//   seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 1, SCMP_A0(SCMP_CMP_EQ, open("darknet.cfg", O_RDONLY)));
//   seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 1, SCMP_A0(SCMP_CMP_EQ, open(filePath, O_RDONLY)));
//   seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 1, SCMP_A0(SCMP_CMP_EQ, open("temp.txt", O_WRONLY)));
  
  seccomp_load(ctx);
}

void makeResult(){
    FILE *result = fopen("results.txt", "w");
    fprintf(result, "");
    fclose(result);
}

void readTemp(const char *dataLine){
    FILE *temp = fopen("temp.txt", "r");
    FILE *result = fopen("results.txt", "a");

    fprintf(result, "[%s]\n", dataLine);
    int ch; 
    while((ch = fgetc(temp)) != EOF)
        fputc(ch, result);

    fclose(temp);
    fclose(result);
    remove("temp.txt");
}

int child(void *arg){
    if(geteuid() == 0 && getegid() == 0){
        seteuid(65534);
        setegid(65534);
    }

    prctl(PR_SET_NO_NEW_PRIVS, 1);

    FILE *tmp = freopen("temp.txt", "w", stdout);

    sandbox();
    image_classifier(filePath, topK);

    fclose(tmp);
    return 0;
}