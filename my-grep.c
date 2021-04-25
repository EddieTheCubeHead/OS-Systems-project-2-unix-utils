#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// I much prefer grep being able to print line data
// this can be toggled with this flag. I would have
// implemented an argument for it with getopt but as 
// flags were out of scope I decided not to do that so 
// as not to make the code more difficult to read and 
// review just for the sake of a vanity feature
#define PRINT_LINE 0

void grep_file(FILE* pFile, char* to_match, char* file_name) {
    
    char* buffer;

    buffer = (char*)malloc(sizeof(char));

    if (buffer == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    size_t read_size;
    size_t buffer_size = 0;
    int line_num = 0;

    while((read_size = getline(&buffer, &buffer_size, pFile)) != -1) {
        line_num++;

        // Making empty line end read from stdin
        if (pFile == stdin && !strcmp("\n", buffer)) {
            break;
        } 

        if (strstr(buffer, to_match) != NULL) {
            if (PRINT_LINE) {
                fprintf(
                    stdout,
                    "In file '%s' on line %d: ",
                    file_name,
                    line_num
                    );

            }
            fprintf(stdout, "%s\n", buffer);
        }
    }

    free(buffer);

    if (pFile != stdin) {
        fclose(pFile);
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    }

    if (argc == 2) {
        grep_file(stdin, argv[1], "stdin");
    } else {
        for (int i = 2; i < argc; i++) {
            FILE* pFile = fopen(argv[i], "r");

            if (pFile == NULL) {
                fprintf(stderr, "my-grep: cannot open file\n");
                exit(1);
            }

            grep_file(pFile, argv[1], argv[i]);
        }
    }
}