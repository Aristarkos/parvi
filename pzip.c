#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 4  // Valitsin säikeiden määräksi 4

typedef struct {
    char *data;
    int length;
} ThreadData;

void *compress_segment(void *arg) {
    ThreadData *segment = (ThreadData *)arg;
    int count = 1;

    for (int i = 0; i < segment->length - 1; i++) {
        if (segment->data[i] == segment->data[i + 1]) {
            count++;
        } else {
            fwrite(&count, sizeof(int), 1, stdout);
            fwrite(&segment->data[i], sizeof(char), 1, stdout);
            count = 1;
        }
    }

    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&segment->data[segment->length - 1], sizeof(char), 1, stdout);

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "pzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "pzip: cannot open file %s\n", argv[1]);
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc(filesize);
    fread(buffer, 1, filesize, fp);
    fclose(fp);

    pthread_t threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];

    int chunk_size = filesize / MAX_THREADS;
    for (int i = 0; i < MAX_THREADS; i++) {
        thread_data[i].data = buffer + i * chunk_size;
        thread_data[i].length = (i == MAX_THREADS - 1) ? (filesize - i * chunk_size) : chunk_size;
        pthread_create(&threads[i], NULL, compress_segment, &thread_data[i]);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    free(buffer);
    return 0;
}