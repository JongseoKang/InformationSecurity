all: main.c input.c queue.c policy.c ./headers/input.h ./headers/policy.h ./headers/queue.h
	gcc main.c input.c queue.c policy.c -std=c11 -o secure_house

clean: secure_house
	rm -f secure_house
