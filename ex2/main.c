#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sort_bus_lines.h"
#include "test_bus_lines.h"

#define MAX_LINE_LENGTH 64
#define NUMBER_REQUEST "Enter number of lines. Then enter\n"
#define LINE_REQUEST "Enter line info. Then enter\n"

#define DISTANCE_ERROR "Error: distance should be an integer between 0 and 1000 (includes)\n"
#define FREQUENCY_ERROR "Error: frequency should be an integer between 1 and 50 (includes)\n"
#define DURATION_ERROR "Error: duration should be an integer between 10 and 100 (includes)\n"
#define NAME_ERROR "Error: bus name should contains only digits and small chars\n"
#define LINES_ERROR "Error: number of lines should be a positive integer\n"
#define INPUT_ERROR "Error: invalid input\n"
#define USAGE_ERROR "Usage: sort_lines <by_distance|by_duration|by_frequency|by_name|test>\n"

#define BUS_NAME_MAX 21

#define DISTANCE_UPPER 1000
#define FREQUENCY_UPPER 50
#define DURATION_UPPER 100

#define DISTANCE_LOWER 0
#define FREQUENCY_LOWER 1
#define DURATION_LOWER 10

#define DIGIT_UPPER '9'
#define DIGIT_LOWER '0'

#define CHAR_LOWER 'a'
#define CHAR_UPPER 'z'

int check_parameters(const char bus_name[],
                     int distance,
                     int duration,
                     int frequency)
{
    for (int name_counter = 0;
         bus_name[name_counter] != '\0';
         name_counter++)
    {
        char current_char = bus_name[name_counter];

        int is_digit = current_char >= DIGIT_LOWER &&
                       current_char <= DIGIT_UPPER;

        int is_small_letter = current_char >= CHAR_LOWER &&
                              current_char <= CHAR_UPPER;

        if (!is_digit && !is_small_letter)
        {
            printf(NAME_ERROR);
            return EXIT_FAILURE;
        }
    }

    if (distance < DISTANCE_LOWER || distance > DISTANCE_UPPER)
    {
        printf(DISTANCE_ERROR);
        return EXIT_FAILURE;
    }

    if (duration < DURATION_LOWER || duration > DURATION_UPPER)
    {
        printf(DURATION_ERROR);
        return EXIT_FAILURE;
    }

    if (frequency < FREQUENCY_LOWER || frequency > FREQUENCY_UPPER)
    {
        printf(FREQUENCY_ERROR);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void reset_busline(const BusLine *copy,BusLine *bus_list, int number_of_lines)
{
    for (int i = 0; i < number_of_lines; i++)
    {
        bus_list[i] = copy[i];
    }
}

void print_bus_lines(const BusLine *start, const BusLine *end)
{
    const BusLine *curr = start;

    while (curr <= end)
    {
        printf("%s,%d,%d,%d\n",
               curr->name,
               curr->distance,
               curr->duration,
               curr->frequency);
        curr++;
    }
}

int run_all_tests(BusLine *bus_list, BusLine *end, int number_of_lines)
{
    BusLine *copy = malloc(sizeof(BusLine) * number_of_lines);

    if (copy == NULL)
    {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < number_of_lines; i++)
    {
        copy[i] = bus_list[i];
    }

    BusLine *copy_end = &copy[number_of_lines - 1];

    bus_quick_sort(bus_list, end, DISTANCE);
    printf("TEST 1 %s: sorted by distance\n", is_sorted_by_distance(bus_list, end) ? "PASSED" : "FAILED");
    printf("TEST 2 %s: same items\n", is_equal(bus_list, end, copy, copy_end) ? "PASSED" : "FAILED");
    reset_busline(copy, bus_list, number_of_lines);

    bus_quick_sort(bus_list, end, DURATION);
    printf("TEST 3 %s: sorted by duration\n", is_sorted_by_duration(bus_list, end) ? "PASSED" : "FAILED");
    printf("TEST 4 %s: same items\n", is_equal(bus_list, end, copy, copy_end) ? "PASSED" : "FAILED");
    reset_busline(copy, bus_list, number_of_lines);

    bus_quick_sort(bus_list, end, FREQUENCY);
    printf("TEST 5 %s: sorted by frequency\n", is_sorted_by_frequency(bus_list, end) ? "PASSED" : "FAILED");
    printf("TEST 6 %s: same items\n", is_equal(bus_list, end, copy, copy_end) ? "PASSED" : "FAILED");
    reset_busline(copy, bus_list, number_of_lines);

    bus_bubble_sort(bus_list, end);
    printf("TEST 7 %s: sorted by name\n", is_sorted_by_name(bus_list, end) ? "PASSED" : "FAILED");
    printf("TEST 8 %s: same items\n", is_equal(bus_list, end, copy, copy_end) ? "PASSED" : "FAILED");
    reset_busline(copy, bus_list, number_of_lines);

    free(copy);
    return EXIT_SUCCESS;
}

BusLine *get_bus(int number_of_lines)
{
    BusLine *bus_list = malloc(sizeof(BusLine) * number_of_lines);

    if (bus_list == NULL)
    {
        return NULL;
    }

    int bus_counter = 0;

    while (bus_counter < number_of_lines)
    {
        printf(LINE_REQUEST);

        char line_input[MAX_LINE_LENGTH];

        if (fgets(line_input, sizeof(line_input), stdin) == NULL)
        {
            free(bus_list);
            return NULL;
        }

        char bus_name[BUS_NAME_MAX];
        int distance, duration, frequency;

        if (sscanf(line_input, "%20[^,],%d,%d,%d",
                   bus_name,
                   &distance,
                   &duration,
                   &frequency) != 4)
        {
            printf(INPUT_ERROR);
            continue;
        }

        if (check_parameters(bus_name, distance, duration, frequency) == EXIT_FAILURE)
        {
            continue;
        }

        strcpy(bus_list[bus_counter].name, bus_name);
        bus_list[bus_counter].distance = distance;
        bus_list[bus_counter].duration = duration;
        bus_list[bus_counter].frequency = frequency;

        bus_counter++;
    }

    return bus_list;
}

int is_valid_arg(const char arg[])
{
    return strcmp(arg, "by_name") == 0 ||
           strcmp(arg, "by_distance") == 0 ||
           strcmp(arg, "by_duration") == 0 ||
           strcmp(arg, "by_frequency") == 0 ||
           strcmp(arg, "test") == 0;
}

int get_number_of_lines(int *number_of_lines)
{
    char input[MAX_LINE_LENGTH];

    while (1)
    {
        printf(NUMBER_REQUEST);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            return EXIT_FAILURE;
        }

        if (sscanf(input, "%d", number_of_lines) == 1 &&
            *number_of_lines > 0)
        {
            return EXIT_SUCCESS;
        }

        printf(LINES_ERROR);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2 || !is_valid_arg(argv[1]))
    {
        printf(USAGE_ERROR);
        return EXIT_FAILURE;
    }

    int number_of_lines;

    if (get_number_of_lines(&number_of_lines) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

    BusLine *bus_list = get_bus(number_of_lines);

    if (bus_list == NULL)
    {
        return EXIT_FAILURE;
    }

    BusLine *end_bus = &bus_list[number_of_lines - 1];

    if (strcmp(argv[1], "by_name") == 0)
    {
        bus_bubble_sort(bus_list, end_bus);
        print_bus_lines(bus_list, end_bus);
    }
    else if (strcmp(argv[1], "by_distance") == 0)
    {
        bus_quick_sort(bus_list, end_bus, DISTANCE);
        print_bus_lines(bus_list, end_bus);
    }
    else if (strcmp(argv[1], "by_duration") == 0)
    {
        bus_quick_sort(bus_list, end_bus, DURATION);
        print_bus_lines(bus_list, end_bus);
    }
    else if (strcmp(argv[1], "by_frequency") == 0)
    {
        bus_quick_sort(bus_list, end_bus, FREQUENCY);
        print_bus_lines(bus_list, end_bus);
    }
    else
    {
        run_all_tests(bus_list, end_bus, number_of_lines);
    }

    free(bus_list);
    return EXIT_SUCCESS;
}