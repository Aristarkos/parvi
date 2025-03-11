#include <stdio.h>
#include <stdlib.h>

void compress_file(FILE *fp) {
    int current_char, next_char;
    int count = 1;

    if ((current_char = fgetc(fp)) == EOF) return;

    while ((next_char = fgetc(fp)) != EOF) {
        if (next_char == current_char) {
            count++;
        } else {
            fwrite(&count, sizeof(int), 1, stdout);
            fwrite(&current_char, sizeof(char), 1, stdout);
            current_char = next_char;
            count = 1;
        }
    }

    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&current_char, sizeof(char), 1, stdout);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "wzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            fprintf(stderr, "wzip: cannot open file %s\n", argv[i]);
            exit(1);
        }
        compress_file(fp);
        fclose(fp);
    }

    return 0;
}