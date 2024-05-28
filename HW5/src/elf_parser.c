#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libelf.h>
#include <fcntl.h>
#include <gelf.h>
#include <unistd.h>

void print_executable_sections(const char *filename) {
    if (elf_version(EV_CURRENT) == EV_NONE) {
        fprintf(stderr, "ELF library initialization failed: %s\n", elf_errmsg(-1));
        exit(EXIT_FAILURE);
    }

    int fd = open(filename, O_RDONLY, 0);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    Elf *e = elf_begin(fd, ELF_C_READ, NULL);
    if (!e) {
        fprintf(stderr, "elf_begin() failed: %s\n", elf_errmsg(-1));
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (elf_kind(e) != ELF_K_ELF) {
        fprintf(stderr, "This is not an ELF file.\n");
        elf_end(e);
        close(fd);
        exit(EXIT_FAILURE);
    }

    size_t shstrndx;
    if (elf_getshdrstrndx(e, &shstrndx) != 0) {
        fprintf(stderr, "elf_getshdrstrndx() failed: %s\n", elf_errmsg(-1));
        elf_end(e);
        close(fd);
        exit(EXIT_FAILURE);
    }

    Elf_Scn *scn = NULL;
    GElf_Shdr shdr;
    char *name;

    printf("Executable Sections:\n");
    printf("  [Nr] Name              Address          Offset\n");
    printf("       Size              EntSize         Flags  Link  Info  Align\n");

    while ((scn = elf_nextscn(e, scn)) != NULL) {
        if (gelf_getshdr(scn, &shdr) != &shdr) {
            fprintf(stderr, "gelf_getshdr() failed: %s\n", elf_errmsg(-1));
            elf_end(e);
            close(fd);
            exit(EXIT_FAILURE);
        }

        if (shdr.sh_flags & SHF_EXECINSTR) {
            name = elf_strptr(e, shstrndx, shdr.sh_name);
            printf("  [%2zu] %-17s %016jx  %016jx\n",
                   elf_ndxscn(scn),
                   name,
                   (uintmax_t)shdr.sh_addr,
                   (uintmax_t)shdr.sh_offset);
            printf("       %016jx  %016jx  %02x     %2u    %2u    %ju\n",
                   (uintmax_t)shdr.sh_size,
                   (uintmax_t)shdr.sh_entsize,
                   shdr.sh_flags,
                   shdr.sh_link,
                   shdr.sh_info,
                   (uintmax_t)shdr.sh_addralign);
        }
    }

    elf_end(e);
    close(fd);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <elf-file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    print_executable_sections(argv[1]);

    return 0;
}
