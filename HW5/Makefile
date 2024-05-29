all: ./src/main.c ./src/csi4109.c ./src/rsa_sign.c ./src/elf_parser.c ./header/elf_parser.h ./header/csi4109.h ./header/rsa_sign.h
	gcc -o signtool ./src/main.c ./src/csi4109.c ./src/rsa_sign.c ./src/elf_parser.c -std=c11 -lssl -lcrypto -lelf -lc

elf:
	sudo apt-get install libelf-dev

elfparser: ./src/elf_parser.c
	gcc -o elf_parser ./src/elf_parser.c -lelf		# ./elf_parser /path/to/your/elf/file

clean:
	rm -rf signtool