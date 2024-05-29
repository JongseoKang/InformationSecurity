all: ./src/main.c ./src/csi4109.c ./src/rsa_sign.c
	gcc -o singtool ./src/main.c ./src/csi4109.c ./src/rsa_sign.c -lssl -lcrypto

elf:
	sudo apt-get install libelf-dev

elfparser: ./src/elf_parser.c
	gcc -o elf_parser ./src/elf_parser.c -lelf		# ./elf_parser /path/to/your/elf/file

