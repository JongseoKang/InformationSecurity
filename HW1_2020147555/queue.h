#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <string.h>
#include <stdlib.h>


typedef struct Queue{
	char *name;
	struct Queue *next;
}Queue;

Queue* createNode(char *name);
int queuePush(Queue **qptr, char *name);
int queuePop(Queue **qptr, char *name);

#endif