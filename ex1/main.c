#include <stdio.h>

#include "cipher.h"
#include "tests.h"
#include <string.h>
#include <_stdlib.h>


// your code goes here

#define MAX_ARGUMENTS 4
#define MIN_ARGUMENT 1
#define ARGUMENT_ERROR "The program receives 1 or 4 arguments only.\n"
#define FIRST_WORD_ERROR "The given argument is invalid.\n"
#define TEST_ERROR "Usage: cipher test\n"
int main(int argc, char *argv[]) {

    if (argc != MIN_ARGUMENT && argc != MAX_ARGUMENTS) {
        printf(ARGUMENT_ERROR);
        return EXIT_FAILURE;
    }

    if (argc == MIN_ARGUMENT) {

        if (strcmp(argv[0], "test") != 0) {
            printf(TEST_ERROR);
            return EXIT_FAILURE;
        }
    }

    /* argc == 4 here */
    if (strcmp(argv[1], "cipher") != 0 && strcmp(argv[1], "decipher") != 0) {
        printf(FIRST_WORD_ERROR);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "cipher") != 0) {
        int k = strtol(argv[3],NULL,10);
        

    }
}