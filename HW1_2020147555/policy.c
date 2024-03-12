#include "./headers/policy.h"

void insertKey(char *user, char *key, House *house){
    realloc(house->insertedKey, SIZE(key));
    strcpy(house->insertedKey, key);
    house->insertState = INSERTED;
    house->lockState = LOCKED;

    printf("KEY %s INSERTED BY %s\n", key, user);
}

void turnKey(char *user, House *house){
    if(house->insertState == UNINSERTED){
        printf("FAILURE %s HAD NO KEY INSERTED\n", user);
    }else{
        for(int i = 0; i < house->numKeys; i++){
            if(strcmp(house->keys[i], house->insertedKey) == 0){
                printf("SUCCESS %s TURNS KEY %s\n", user, house->insertedKey);
                house->lockState = UNLOCKED;
            }
        }

        printf("FAILURE %s HAD INVALID KEY %s INSERTED\n", user, house->insertedKey);
    }
}

void enterHouse(char *user, House *house){
    if(house->lockState == UNLOCKED){
        printf("ACCESS ALLOWED\n");
        enqueue(house->accessQueue, user);
        house->lockState = LOCKED;
    }else printf("ACCESS DENIED\n");
}

void insideMemebers(House *house){
    if(isEmpty(house->accessQueue)) printf("NOBODY HOME\n");
    else displayQueue(house->accessQueue);
}

void changeLocks(int n, char **nameAndKeys , House *house){
    if(house->ownerState == OWNER_INSIDE && strcmp(house->owner, nameAndKeys[0])){
        printf("LOCK CHANGED\n");
        
        house->numKeys = n - 1;
        realloc(house->keys, house->numKeys * sizeof(char*));

        for(int i = 0; i < house->numKeys; i++){
            house->keys[i] = malloc(SIZE(nameAndKeys + i));
            strcpy(house->keys[i], nameAndKeys + i);
        }

        house->lockState = LOCKED;
    }else printf("LOCK CHANGED DENIED\n");
}

void leaveHouse(char *user, House *house){
    if(dequeue(house->accessQueue, user)) printf("%s LEFT\n", user);
    else printf("%s NOT HERE", user);
}