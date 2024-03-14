#include <stdio.h>
#include "./headers/input.h"
#include "./headers/policy.h"

int setHouse(int n, char **ownerAndKeys, House *house);
int freeHouse(House *house);

int main(int agrc, char **agrv){
	House house;
	char *input, **words;
	int numWords;
	char **ownerAndKeys = malloc((agrc - 1) * sizeof(char*));

	for(int i = 0; i < agrc - 1; i++){
		ownerAndKeys[i] = malloc(SIZE(agrv[i + 1]));
		strcpy(ownerAndKeys[i], agrv[i + 1]);
	}

	setHouse(agrc - 1, ownerAndKeys, &house);
	for(int i = 0; i < agrc - 1; i++) free(ownerAndKeys[i]);
	free(ownerAndKeys);

	input = getInput();
	words = splitInput(input, &numWords);
	while(numWords > 1 || strlen(words[0]) > 0){
		if(keysNamesCheck(words, numWords) == INVALID){
			printf("ERROR\n");
		}
		else if(insertKeyCheck(words, numWords) == VALID){
			insertKey(words[2], words[3], &house);
		}
		else if(turnKeyCheck(words, numWords) == VALID){
			turnKey(words[2], &house);
		}
		else if(enterHouseCheck(words, numWords)){
			enterHouse(words[2], &house);
		}
		else if(insideMemebersCheck(words, numWords) == VALID){
			insideMemebers(&house);
		}
		else if(changeLocksCheck(words, numWords) == VALID){
			char **nameAndKeys = malloc((numWords - 2) * sizeof(char*));

			for(int i = 0; i < numWords - 2; i++){
				nameAndKeys[i] = malloc(SIZE(words[i + 2]));
				strcpy(nameAndKeys[i], words[i + 2]);
			}

			changeLocks(numWords - 2, nameAndKeys, &house);
			
			for(int i = 0; i < numWords - 2; i++) free(nameAndKeys[i]);
			free(nameAndKeys);
		}
		else if(leaveHouseCheck(words, numWords) == VALID){
			leaveHouse(words[2], &house);
		}
		else{
			printf("ERROR");
		}

		input = getInput();
		words = splitInput(input, &numWords);
	}
	
	free(input);
	freeWords(words, numWords);
	
	freeHouse(&house);
	return 0;
}

int setHouse(int n, char **ownerAndKeys, House *house){
	house->owner = malloc(SIZE(ownerAndKeys[0]));
	strcpy(house->owner, ownerAndKeys[0]);
	house->ownerState = OWNER_OUTSIDE;

	house->numKeys = n;
	house->keys = malloc(n * sizeof(char*));

	house->keys[0] = malloc(SIZE(SECRET_KEY));
	for(int i = 1; i < n; i++){
		house->keys[i] = malloc(SIZE(ownerAndKeys[i]));
		strcpy(house->keys[i], ownerAndKeys[i]);
	}

	house->accessQueue = malloc(sizeof(Queue));
	initializeQueue(house->accessQueue);

	house->insertedKey= malloc(5 * sizeof(char));
	house->lockState = LOCKED;
	house->insertState = UNINSERTED;

	return 0;
}

int freeHouse(House *house){
	free(house->owner);
	
	for(int i = 0; i < house->numKeys; i++) free(house->keys[i]);
	free(house->keys);

	clearQueue(house->accessQueue);
	free(house->accessQueue);

	free(house->insertedKey);
	return 0;
}