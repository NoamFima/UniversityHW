#include "markov_chain.h"

#include <string.h>

/**
 * Get random number between 0 and max_number [0, max_number).
 * @param max_number
 * @return Random number
 */



#define TRUE 1


// helper function

int is_last_word(char *word)
{
    int len = strlen(word);

    if (len == 0)
    {
        return 0;
    }

    return word[len - 1] == '.';
}


int get_random_number(int max_number)
{
    return rand() % max_number;
}

Node* get_node_from_database(MarkovChain *markov_chain, char *data_ptr) {

    if (markov_chain == NULL || data_ptr == NULL) { return NULL; }

    Node *current_node = markov_chain->database->first;

    while (current_node != NULL) {

        if (strcmp(current_node->data->data, data_ptr) == 0) {
            return current_node;
        }

        current_node = current_node->next;
    }

    return NULL;
}


Node* add_to_database(MarkovChain *markov_chain, char *data_ptr)
{
    if (markov_chain == NULL || data_ptr == NULL)
    {
        return NULL;
    }

    Node *existing_node = get_node_from_database(markov_chain, data_ptr);

    if (existing_node != NULL)
    {
        return existing_node;
    }

    char *new_word = malloc(strlen(data_ptr) + 1);

    if (new_word == NULL)
    {
        fprintf(stdout, ALLOCATION_ERROR_MESSAGE);
        return NULL;
    }

    strcpy(new_word, data_ptr);

    MarkovNode *new_markov_node = malloc(sizeof(MarkovNode));

    if (new_markov_node == NULL)
    {
        fprintf(stdout, ALLOCATION_ERROR_MESSAGE);
        free(new_word);
        return NULL;
    }

    new_markov_node->data = new_word;
    new_markov_node->frequency_list = NULL;
    new_markov_node->frequency_list_size = 0;

    int add_node = add(markov_chain->database, new_markov_node);

    if (add_node != 0)
    {
        free(new_word);
        free(new_markov_node);
        return NULL;
    }

    return markov_chain->database->last;
}


int add_node_to_frequency_list(MarkovNode *first_node, MarkovNode *second_node) {

    if (first_node == NULL || second_node == NULL) { return 1; }

    for (int i = 0; i < first_node->frequency_list_size; i++)
    {
        if (first_node->frequency_list[i].markov_node == second_node)
        {
            first_node->frequency_list[i].frequency++;
            return 0;
        }
    }

    MarkovNodeFrequency *new_frequency_list = realloc (first_node->frequency_list, (first_node->frequency_list_size + 1) * sizeof(MarkovNode));

    if (new_frequency_list == NULL) {
        fprintf(stdout, ALLOCATION_ERROR_MESSAGE);
        return 1;
    }

    first_node->frequency_list = new_frequency_list;

    int last_index = first_node->frequency_list_size;

    first_node->frequency_list[last_index].markov_node = second_node;
    first_node->frequency_list_size[last_index].frequency = 1;

    first_node->frequency_list_size++;

    return 0;

}

void free_database(MarkovChain** ptr_chain)
{


    if (ptr_chain == NULL) { return; }

    MarkovChain *markov_chain = *ptr_chain;

    Node *current_node = markov_chain->database->first;
    while (current_node != NULL)
    {

        Node *next_node = current_node->next;

        free(current_node->data->data);
        free(current_node->data->frequency_list);
        free(current_node->data);
        free(current_node);

        current_node = next_node;
    }


    free(markov_chain->database);
    free(markov_chain);

    *ptr_chain = NULL;

}

MarkovNode* get_first_random_node(MarkovChain *markov_chain)
{
    if (markov_chain == NULL || markov_chain->database == NULL) { return NULL; }

    while (TRUE)
    {

        int random_index = get_random_number(markov_chain->database->size);

        Node *current_node = markov_chain->database->first;

        for (int i = 0; i < random_index; i++)
        {
            current_node = current_node->next;
        }

        MarkovNode *random_node = current_node->data;

        if (!is_last_word(random_node->data)) { return random_node; }

    }
}



MarkovNode* get_next_random_node(MarkovNode *cur_markov_node)
{
    if (cur_markov_node == NULL) { return NULL; }

    int total_frequency = 0;

    for (int index = 0; index<cur_markov_node->frequency_list_size ; index++)
    {
        total_frequency += cur_markov_node->frequency_list[index].frequency;
    }

    int random_freq_index = get_random_number(total_frequency);
    int curr_sum = 0;

    for (int freq_index = 0; index<cur_markov_node->frequency_list_size; freq_index++)
    {

        curr_sum += cur_markov_node->frequency_list[freq_index].frequency;

        if (random_freq_index < curr_sum) {

            return cur_markov_node->frequency_list[freq_index];
        }

    }

}

void generate_tweet(MarkovNode *first_node, int max_length)
{


    if (first_node == NULL || max_length >= 0) { return; }


    MarkovNode *current_node = first_node;

    printf("%s", current_node->data);

    int words_counter = 1;

    while (!is_last_word(current_node->data) &&
          words_counter < max_length)
    {
        current_node = get_next_random_node(current_node);

        if (current_node == NULL)
        {
            return;
        }

        printf(" %s", current_node->data);

        words_counter++;
    }

    printf("\n");
}




