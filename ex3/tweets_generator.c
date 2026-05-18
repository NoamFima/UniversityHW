//Don't change the macros!
#define FILE_PATH_ERROR "Error: incorrect file path\n"
#define NUM_ARGS_ERROR  "Usage: tweets_generator <seed> <num_tweets> "\
                        "<file_path> [words_to_read] [seed_word]\n"

#define DELIMITERS " \n\t\r"
#define MAX_LINE_LENGTH 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "markov_chain.h"

int is_last_word(char *word)
{
    int len = strlen(word);

    if (len == 0)
    {
        return 0;
    }

    return word[len - 1] == '.';
}


int fill_database(FILE *fp, int words_to_read, MarkovChain *markov_chain) {

    char line[MAX_LINE_LENGTH];

    int word_counter = 0;
    MarkovNode *prev_node = NULL;


    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        char *seperated_word = strtok(line,DELIMITERS);

        while (seperated_word != NULL)
        {

            Node *current_node = add_to_database(markov_chain, seperated_word);

            if (current_node == NULL) { return EXIT_FAILURE; }

            MarkovNode *curr_markov_node = current_node->data;

            if (prev_node != NULL && !is_last_word(prev_node->data))
            {
                if (add_node_to_frequency_list(prev_node, curr_markov_node) == EXIT_FAILURE)
                {
                    return EXIT_FAILURE;
                }
            }

            prev_node = curr_markov_node;
            word_counter++;

            if (words_to_read != -1 &&
                word_counter >= words_to_read)
            {
                return EXIT_FAILURE;
            }

            seperated_word = strtok(NULL, DELIMITERS);
        }

        return EXIT_SUCCESS;

    }

}

int main(int argc, char *argv[])
{

    if (argc != 4 && argc != 5 && argc != 6) {
        fprintf(stdout , NUM_ARGS_ERROR);
        return EXIT_FAILURE;
    }


    unsigned int seed = (unsigned int) atoi(argv[1]);
    int tweets_num = atoi(argv[2]);
    char *path = argv[3];

    int words_to_read = -1;

    if (argc >= 5)
    {
        words_to_read = atoi(argv[4]);
    }

    srand(seed);

    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        fprintf(stdout,FILE_PATH_ERROR);
        return FAILURE_EXIT;
    }


    MarkovChain *markov_chain = malloc(sizeof(MarkovChain));

    if (markov_chain == NULL)
    {
        fprintf(stdout,ALLOCATION_ERROR_MESSAGE);
        fclose(fp);
        return FAILURE_EXIT;
    }


    LinkedList *database = malloc(sizeof(LinkedList));

    if (database == NULL)
    {

        fprintf(stdout,ALLOCATION_ERROR_MESSAGE);
        free(markov_chain);
        fclose(fp);
        return FAILURE_EXIT;
    }

    database->first = NULL;
    database->last = NULL;
    database->size = 0;

    markov_chain->database = database;

    if (fill_database(fp, words_to_read, markov_chain) == EXIT_FAILURE)
    {
        free_database(&markov_chain);
        fclose(fp);
        return EXIT_FAILURE;
    }

    fclose(fp);

    for (int i = 0; i < tweets_num; i++)
    {
        MarkovNode *first_node =
                get_first_random_node(markov_chain);

        printf("Tweet %d: ", i + 1);

        generate_tweet(first_node, 20);
    }

    free_database(&markov_chain);

    return SUCCESS_EXIT;
    
}

