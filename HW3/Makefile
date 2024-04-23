all: main.c
	gcc -o cryp main.c -lssl -lcrypto -std=c11

test: test.c
	gcc -o test test.c -lssl -lcrypto -std=c11

clean:
	rm -rf cryp