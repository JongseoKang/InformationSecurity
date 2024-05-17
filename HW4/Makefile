all: libdarknet_predict.so main.c
	gcc main.c -o secure_classifier -std=c11 -ldl

test: test.c
	gcc test.c -o test -std=c11
clean:
	rm -rf secure_classifier