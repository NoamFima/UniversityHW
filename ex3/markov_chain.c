#include "markov_chain.h"

#include <string.h>

/**
 * Get random number between 0 and max_number [0, max_number).
 * @param max_number
 * @return Random number
 */
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


Node* add_to_database(MarkovChain *markov_chain, char *data_ptr) {


    if (markov_chain == NULL || data_ptr == NULL) { return NULL; }

    Node *existing_node = get_node_from_database(markov_chain, data_ptr);

    if (existing_node != NULL) { return existing_node; }

    char *new_word = malloc(strlen(data_ptr) + 1);

    if (new_word == NULL) { return NULL; }

    strcpy(new_word, data_ptr);

    MarkovNode *new_markov_node = malloc (sizeof(MarkovNode));

    if (new_markov_node == NULL) {
        free(new_word);
        return NULL;
    }

    new_markov_node->data = new_word;
    new_markov_node->frequency_list = NULL;


    int add_node = add(markov_chain->database, new_markov_node);

    if (add_node != 0) {
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
