#include "queue.h"
#incluce "policy.h"

Queue* createNode(char *name){
    Queue *p = malloc(sizeof(Queue));
    p->name = malloc(SIZE(name));
    strcpy(p->name, name);
    p->next = NULL; // This will be set on insertion
    return p;
}

int queuePush(Queue **qptr, char *name){
    Queue **it = qptr;

    while(*it != NULL){
        it = &(*it)->next;
    }

    *it = createNode(name); 

    return 0;
}

int queuePop(Queue **qptr, char *name){
    Queue **curr = qptr, **prev = qptr;
    int leaved = 0;

    while(*it != NULL){
        if(strcmp((*curr)->next->name, name) == 0){
            (*prev)->next = (*curr)->next;
            free((*free)->next->name);
            free((*head)->next);
            head->next = temp;
            break;
        }
        head = head->next;
    }

    return leaved;
}
