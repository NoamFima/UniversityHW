#include "test_bus_lines.h"
#include <string.h>

#include <stdlib.h>
//TODO add implementation here


#define TRUE 1
#define FALSE 0

int is_sorted_by_distance(const BusLine *start, const BusLine *end)
{
    const BusLine *current = start;


    while (current < end)
    {
        if (current->distance > (current + 1)->distance)
        {
            return FALSE;

        }

        current++;
    }
    return TRUE;
}



int is_sorted_by_duration(const BusLine *start, const BusLine *end)
{
    const BusLine *current = start;

    while (current < end)
    {
        if (current->duration > (current + 1)->duration)
        {
            return FALSE;
        }

        current++;
    }

    return TRUE;
}


int is_sorted_by_frequency(const BusLine *start, const BusLine *end)
{
    const BusLine *current = start;

    while (current < end)
    {
        if (current->frequency > (current + 1)->frequency)
        {
            return FALSE;
        }

        current++;
    }

    return TRUE;
}



int is_sorted_by_name(const BusLine *start, const BusLine *end)
{
    const BusLine *current = start;

    while (current < end)
    {
        if (strcmp(current->name, (current + 1)->name) > 0)
        {
            return FALSE;
        }

        current++;
    }

    return TRUE;
}

int is_equal(const BusLine *start_sorted, const BusLine *end_sorted, const BusLine *start_original, const BusLine *end_original)
{
    if (end_sorted - start_sorted != end_original - start_original)
    {
        return FALSE;
    }

    const BusLine *current_original = start_original;

    while (current_original <= end_original)
    {
        int found = FALSE;
        const BusLine *current_sorted = start_sorted;

        while (current_sorted <= end_sorted)
        {
            if (strcmp(current_original->name, current_sorted->name) == 0)
            {
                found = TRUE;
                break;
            }

            current_sorted++;
        }

        if (!found)
        {
            return FALSE;
        }

        current_original++;
    }

    return TRUE;
}