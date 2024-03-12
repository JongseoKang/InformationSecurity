#ifndef _POLICY_H_
#define _POLICY_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

#ifndef SIZE
#define SIZE(str) (strlen(str) + 1)
#endif

#define LOCKED 1
#define UNLOCKED 0
#define INSERTED 1
#define UNINSERTED 0
#define OWNER_INSIDE 1
#define OWNER_OUTSIDE 0

#define SECRET_KEY "FIREFIGHTER_SECRET_KEY"

typedef struct House{
	char **keys;
	int numKeys;

	Queue *accessQueue;
	int numAccess;

	char *owner;
	int ownerState;

	char *insertedKey;
	int insertState;
	int lockState;
}House;

int insertKey(char *user, char *key, House *house);
int turnKey(char *user, House *house);
int enterHouse(char *user, House *house);
int insideMemebers(House *house);
int changeLocks(int n, char **nameAndKeys , House *house);
int leaveHouse(char *user, House *house);

#endif