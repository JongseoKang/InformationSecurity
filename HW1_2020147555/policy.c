# include "./headers/policy.h"
# include "./headers/queue.h"

int insertKey(char *user, char *key, House *house){
    house->insertedKey = realloc(SIZE(key) * sizeof(char));
    strcpy(house->insertedKey, key);
    house->insertState = INSERTED;
    house->lockState = LOCKED;

    printf("KEY %s INSERTED BY %s\n", key, user);
    return 0;
}

int turnKey(char *user, House *house){
    if(house->insertState == UNINSERTED){
        printf("FAILURE %s HAD NO KEY INSERTED\n", user);
        return 0;
    }else{
        for(int i = 0; i < house->numKeys; i++){
            if(strcmp(house->keys[i], house->insertedKey) == 0){
                printf("SUCCESS %s TURNS KEY %s\n", user, house->insertedKey);
                house->lockState = UNLOCKED;
                return 0;
            }
        }

        printf("FAILURE %s HAD INVALID KEY %s INSERTED\n", user, house->insertedKey);
        return 0;
    }
}

int enterHouse(char *user, House *house){
    if(house->lockState == UNLOCKED){
        printf("ACCESS ALLOWED\n");
        queuePush(&(house->accessQueue), user);
        house->lockState = LOCKED;
    }else printf("ACCESS DENIED\n");
    
    return 0;
}

int insideMemebers(House *house){
    Queue *head = house->accessQueue;

    if(head->next == NULL){
        printf("NOBODY HOME\n");
    }else{
        while(head->next != NULL){
            printf("%s ", head->name);
            head = head->next;
        }
        printf("\n");
    }

    return 0;
}

int changeLocks(int n, char **nameAndKeys , House *house){
    house->lockState = LOCKED;

    if(house->ownerState == OWNER_INSIDE && strcmp(house->owner, nameAndKeys[0])){
        printf("LOCK CHANGED\n");

    }else printf("LOCK CHANGED DENIED\n");

    return 0;
}

int leaveHouse(char *user, House *house){
    
}