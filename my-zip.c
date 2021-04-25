#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void zip_file(FILE* pFile) {
    char* buffer;

    buffer = (char*)malloc(sizeof(char));

    if (buffer == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    size_t read_size;
    size_t buffer_size = 0;

    char current_char = '\0';
    int run_length = 0;

    while((read_size = getline(&buffer, &buffer_size, pFile)) != -1) {

        // Making empty line end read from stdin
        if (pFile == stdin && !strcmp("\n", buffer)) {
            break;
        }

        for (int i = 0; i < read_size; i++) {
            if (current_char == buffer[i]) {
                run_length++;
            } else {
                if (run_length != 0) {
                    fwrite(&run_length, sizeof(run_length), 1, stdout);
                    fwrite(&current_char, 1, 1, stdout);
                }
                current_char = buffer[i];
                run_length = 1;
            }
        }
    }

    if (current_char != '\0' && run_length > 0) {
        fwrite(&run_length, sizeof(run_length), 1, stdout);
        fwrite(&current_char, 1, 1, stdout);
    }

    free(buffer);
    
    if (pFile != stdin) {
        fclose(pFile);
    }
}

int main(int argc, char* argv[]) {

    if (argc == 1) {
        zip_file(stdin);
    } else {
        for (int i = 1; i < argc; i++) {
            FILE* pFile = fopen(argv[i], "r");

            if (pFile == NULL) {
                fprintf(stderr, "my-zip: cannot open file\n");
                exit(1);
            }

            zip_file(pFile);
        }
    }
}