#include "../header/elf_parser.h"

unsigned char *parseExecScn(const char *filename, size_t *msgSize) {
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

    unsigned char *retMsg = malloc(0);
    *msgSize = 0;

    while ((scn = elf_nextscn(e, scn)) != NULL) {
        if (gelf_getshdr(scn, &shdr) != &shdr) {
            fprintf(stderr, "gelf_getshdr() failed: %s\n", elf_errmsg(-1));
            elf_end(e);
            close(fd);
            exit(EXIT_FAILURE);
        }

        if (shdr.sh_flags & SHF_EXECINSTR) {
            // name = elf_strptr(e, shstrndx, shdr.sh_name);
            // printf("  [%2zu] %-17s %016jx  %016jx\n",
            //        elf_ndxscn(scn),
            //        name,
            //        (uintmax_t)shdr.sh_addr,
            //        (uintmax_t)shdr.sh_offset);
            // printf("       %016jx  %016jx  %02x     %2u    %2u    %ju\n",
            //        (uintmax_t)shdr.sh_size,
            //        (uintmax_t)shdr.sh_entsize,
            //        shdr.sh_flags,
            //        shdr.sh_link,
            //        shdr.sh_info,
            //        (uintmax_t)shdr.sh_addralign);
            
            // Read section data
            Elf_Data *data = elf_getdata(scn, NULL);
            if (!data) {
                fprintf(stderr, "elf_getdata() failed: %s\n", elf_errmsg(-1));
                elf_end(e);
                close(fd);
                exit(EXIT_FAILURE);
            }

            retMsg = realloc(retMsg, (*msgSize + data->d_size) * sizeof(unsigned char));

            for (size_t i = 0; i < data->d_size; i++)
                retMsg[*msgSize + i] = ((unsigned char*)data->d_buf)[i];
            *msgSize += data->d_size;
        }
    }

    elf_end(e);
    close(fd);

    return retMsg;
}

unsigned char *parseSignScn(const char *filename, size_t *msgSize){
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

    unsigned char *retMsg = malloc(0);
    *msgSize = 0;

    while ((scn = elf_nextscn(e, scn)) != NULL) {
        if (gelf_getshdr(scn, &shdr) != &shdr) {
            fprintf(stderr, "gelf_getshdr() failed: %s\n", elf_errmsg(-1));
            elf_end(e);
            close(fd);
            exit(EXIT_FAILURE);
        }

        name = elf_strptr(e, shstrndx, shdr.sh_name);
        if (strcmp(name, ".signature") == 0){
            // Read section data
            Elf_Data *data = elf_getdata(scn, NULL);
            if (!data) {
                fprintf(stderr, "elf_getdata() failed: %s\n", elf_errmsg(-1));
                elf_end(e);
                close(fd);
                exit(EXIT_FAILURE);
            }

            retMsg = realloc(retMsg, (*msgSize + data->d_size) * sizeof(unsigned char));

            for (size_t i = 0; i < data->d_size; i++)
                retMsg[*msgSize + i] = ((unsigned char*)data->d_buf)[i];
            *msgSize += data->d_size;
        }
    }

    elf_end(e);
    close(fd);

    return retMsg;
}