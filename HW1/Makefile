all: ./source/main.c ./source/input.c ./source/queue.c ./source/policy.c ./headers/input.h ./headers/policy.h ./headers/queue.h
	gcc ./source/main.c ./source/input.c ./source/queue.c ./source/policy.c -std=c11 -o secure_house

clean: secure_house
	rm -f secure_house
