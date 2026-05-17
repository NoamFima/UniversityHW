//Don't change the macros!
#define FILE_PATH_ERROR "Error: incorrect file path\n"
#define NUM_ARGS_ERROR  "Usage: tweets_generator <seed> <num_tweets> "\
                        "<file_path> [words_to_read] [seed_word]\n"

#define DELIMITERS " \n\t\r"
#define MAX_LINE_LENGTH 1000
#include <stdio.h>
#include <stdlib.h>

#include "markov_chain.h"

int tweets_generator (int seed, int num_tweets , char *file_path, int words_to_read, char *seed_word)
{

    srand(seed);

    FILE *fp = fopen(file_path, "r");

    if (!fp) {

        printf(FILE_PATH_ERROR);

        return EXIT_FAILURE;
    }


    MarkovChain *markov_chain = malloc (sizeof(MarkovChain));

    if (markov_chain == NULL)
    {
        fclose(fp);
        return EXIT_FAILURE;
    }

    markov_chain->database = malloc(sizeof(LinkedList));

    if (markov_chain->database == NULL)
    {
        free(markov_chain);
        fclose(fp);
        return EXIT_FAILURE;
    }



}

