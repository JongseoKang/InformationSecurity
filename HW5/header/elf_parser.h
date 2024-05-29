#ifndef _ELF_PARSER_H_

#define _ELF_PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libelf.h>
#include <fcntl.h>
#include <gelf.h>
#include <unistd.h>

unsigned char *parseExecScn(const char *filename, size_t *msgSize);
unsigned char *parseSignScn(const char *filename, size_t *msgSize);

#endif