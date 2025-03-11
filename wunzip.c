#include <stdio.h>
#include <stdlib.h>

void decompress_file(FILE *fp) {
    int count;
    char c;

    while (fread(&count, sizeof(int), 1, fp) == 1) {
        fread(&c, sizeof(char), 1, fp);
        for (int i = 0; i < count; i++) {
            putchar(c);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (!fp) {
            fprintf(stderr, "wunzip: cannot open file %s\n", argv[i]);
            exit(1);
        }
        decompress_file(fp);
        fclose(fp);
    }

    return 0;
}