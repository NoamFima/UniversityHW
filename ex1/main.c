#include <stdio.h>

#include "cipher.h"
#include "tests.h"
#include <string.h>
#include <stdlib.h>


// your code goes here

#define MAX_ARGUMENTS 5
#define MIN_ARGUMENT 2
#define ARGUMENT_ERROR "The program receives 1 or 4 arguments only.\n"
#define FIRST_WORD_ERROR "The given argument is invalid.\n"
#define TEST_ERROR "Usage: cipher test\n"
#define FILE_ERROR "The given file is invalid.\n"
#define INCOMPATIBLE_VALUES "The given shift is invalid.\n"
#define BUFFER 1024

#include <ctype.h>

int isInt(char *num) {
    if (num[0] == '\0') return 0;

    int curr_digit = 0;

    if (num[0] == '-' || num[0] == '+'
        ) {
        curr_digit ++;
    }

    if (num[curr_digit] == '\0') return 0;

    for (; num[curr_digit] != '\0'; curr_digit++) {
        if (!isdigit((unsigned char)num[curr_digit])) {
            return 0;
        }
    }

    return 1;
}

int run_all_tests() {

    if (test_cipher_non_cyclic_lower_case_positive_k() != 0) { return EXIT_FAILURE; }

    if (test_cipher_cyclic_lower_case_special_char_positive_k() != 0) { return EXIT_FAILURE; }

    if (test_cipher_non_cyclic_lower_case_special_char_negative_k()!= 0) { return EXIT_FAILURE; }

    if (test_cipher_cyclic_lower_case_negative_k () != 0) { return EXIT_FAILURE; }

    if (test_cipher_cyclic_upper_case_positive_k  () != 0) { return EXIT_FAILURE; }

    if (test_decipher_non_cyclic_lower_case_positive_k() != 0) { return EXIT_FAILURE; }

    if (test_decipher_cyclic_lower_case_special_char_positive_k () != 0) { return EXIT_FAILURE; }

    if (test_decipher_non_cyclic_lower_case_special_char_negative_k () != 0) { return EXIT_FAILURE; }

    if (test_decipher_cyclic_lower_case_negative_k () != 0) { return EXIT_FAILURE; }

    if (test_decipher_cyclic_upper_case_positive_k () != 0) { return EXIT_FAILURE; }

    return EXIT_SUCCESS;
}

int cipher_file(char input_file[], char output_file[],int k) {
    char curr_line[BUFFER];
    FILE *input = fopen(input_file,"r");
    FILE *output = fopen(output_file,"w");

    if (!input) {
        printf(FILE_ERROR);
        return EXIT_FAILURE;
    }

    while (fgets(curr_line, sizeof(curr_line), input)) {
        cipher(curr_line, k);
        fputs(curr_line, output);
    }

    while (fgets(curr_line, sizeof(curr_line), input)) {
        cipher(curr_line, k);
        fputs(curr_line, output);
    }

    fclose(input);
    fclose(output);
    return EXIT_SUCCESS;
}

int decipher_file(char input_file[], char output_file[],int k) {
    char curr_line[BUFFER];
    FILE *input = fopen(input_file,"r");
    FILE *output = fopen(output_file,"w");

    if (!input) {
        fprintf(stderr,FILE_ERROR);
        return EXIT_FAILURE;
    }

    while (fgets(curr_line, sizeof(curr_line), input)) {
        decipher(curr_line, k);
        fputs(curr_line, output);
    }

    fclose(input);
    fclose(output);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {

    if (argc != MIN_ARGUMENT && argc != MAX_ARGUMENTS) {
        printf(ARGUMENT_ERROR);
        return EXIT_FAILURE;

    }

    if (argc == MIN_ARGUMENT) {

        if (strcmp(argv[1], "test") != 0) {
            fprintf(stderr,TEST_ERROR);
            return EXIT_FAILURE;

        }else {

            return run_all_tests();
        }
    }
    /* argc == 4 here */
    if (strcmp(argv[1], "cipher") != 0 && strcmp(argv[1], "decipher") != 0) {
        fprintf(stderr,FIRST_WORD_ERROR);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "cipher") == 0) {

        if (!isInt(argv[4])) {
            fprintf(stderr,INCOMPATIBLE_VALUES);
            return EXIT_FAILURE;
        }

        int k = strtol(argv[4], NULL, 10);

        return cipher_file(argv[2], argv[3], k);

    } else if (strcmp(argv[1], "decipher") == 0) {

        if (!isInt(argv[4])) {
            fprintf(stderr,INCOMPATIBLE_VALUES);
            return EXIT_FAILURE;
        }
        int k = strtol(argv[4], NULL, 10);
        return decipher_file(argv[2], argv[3], k);
    }
}