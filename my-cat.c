#include <stdio.h>
#include <stdlib.h>

void print_file(char* file_name) {
    FILE* pFile = fopen(file_name, "r");

    if (pFile == NULL) {
        fprintf(stderr, "my-cat: cannot open file\n");
        exit(1);
    }

    char* buffer;

    buffer = (char*)malloc(sizeof(char));

    if (buffer == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    size_t read_size;
    size_t buffer_size = 0;

    while((read_size = getline(&buffer, &buffer_size, pFile)) != -1) {
        // I've learned that formatting is better if you ever need changes
        // in the future (instead of just raw printing buffer)
        fwrite(buffer, read_size, 1, stdout);
    }
    fwrite("\n", 1, 1, stdout);

    free(buffer);
    fclose(pFile);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: too few arguments.\n");
        printf("Usage: './my-cat [file1] [file2]... [fileN]'\n");
        printf("The program can concat any number of files from one up.\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        print_file(argv[i]);
    }
}