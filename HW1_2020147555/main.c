#include <stdio.h>

#include "./headers/input.h"
#include "./headers/policy.h"

int setHouse(int n, int *ownerAndKeys, House *house);
int freeHouse(House *house);

int main(int agrc, char **agrv){
	House house;

	setHouse(agrc, agrv, &house);

	
	freeHouse(&house);
	return 0;
}

int setHouse(int n, int *ownerAndKeys, House *house){
	house->owner = malloc(SIZE(ownerAndKeys[0]));
	house->ownerState = OWNER_INSIDE;

	house->numKeys = 5;
	house->keys = malloc(house->numKeys * sizeof(char*));
	changeLocks(n, ownerAndKeys, house);
	house->ownerState = OWNER_OUTSIDE;

	house->numAccess = 0;
	house->accessQueue = NULL;	//	has to be modified

	house->insertedKey= malloc(5 * sizeof(char));
	house->lockState = LOCKED;
	house->insertState = UNINSERTED;

	return 0;
}

int freeHouse(House *house){
	free(house->owner);
	
	for(int i = 0; i < house->numKeys; i++) free(house->keys[i]);
	free(house->keys);

	Queue *head, *temp;
	head = house->accessQueue;
	while(head->next != NULL){
		free(head->name);
		temp = head->next;
		free(head);
		head = temp;
	}
	free(head);

	free(house->insertedKey);
	return 0;
}