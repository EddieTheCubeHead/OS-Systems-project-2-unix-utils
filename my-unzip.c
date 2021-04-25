#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void unzip_file(FILE* pFile) {
    int run_length = 0;
    char character = '\0';
    size_t read_success = 0;

    while ((read_success = fread(&run_length, sizeof(int), 1, pFile)) == 1) {
        fread(&character, 1, 1, pFile);

        for (int i = 0; i < run_length; i++) {
            fprintf(stdout, "%c", character);
        }
    }

    fclose(pFile);
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: ./my-unzip file");
        exit(1);
    } else {
        FILE* pFile = fopen(argv[1], "r");

        if (pFile == NULL) {
            fprintf(stderr, "my-unzip: cannot open file\n");
            exit(1);
        }

        unzip_file(pFile);
    }
}