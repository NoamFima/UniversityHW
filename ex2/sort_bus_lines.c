#include "sort_bus_lines.h"
#include <string.h>

//TODO add implementation here
#define TRUE 1
#define NEXT 1
#define FALSE 0

void bus_quick_sort(BusLine *start, BusLine *end, SortType sort_type)
{
    if (start >= end)
    {
        return;
    }

    BusLine *pivot = partition(start, end, sort_type);

    bus_quick_sort(start, pivot - NEXT, sort_type);

    bus_quick_sort(pivot + NEXT, end, sort_type);
}

void bus_bubble_sort(BusLine *start, BusLine *end)
{
    for (BusLine *outer = start; outer < end; outer++)
    {
        for (BusLine *inner = start; inner < end - (outer - start); inner++)
        {
            if (strcmp(inner->name, (inner + NEXT)->name) > FALSE)
            {
                BusLine temp = *inner;
                *inner = *(inner + NEXT);
                *(inner + NEXT) = temp;
            }
        }
    }
}

BusLine *partition(BusLine *start, BusLine *end,SortType sort_type)
{
    BusLine pivot_bus = *end;

    BusLine *starter = start;

    for (BusLine *pointer_bus = start;
         pointer_bus < end;
         pointer_bus++)
    {
        int should_swap = 0;

        if (sort_type == DISTANCE)
        {
            if (pointer_bus->distance < pivot_bus.distance)
            {
                should_swap = TRUE;
            }
        }

        else if (sort_type == FREQUENCY)
        {
            if (pointer_bus->frequency < pivot_bus.frequency)
            {
                should_swap = TRUE;
            }
        }

        else if (sort_type == DURATION)
        {
            if (pointer_bus->duration < pivot_bus.duration)
            {
                should_swap = TRUE;
            }
        }

        if (should_swap)
        {
            BusLine temp = *starter;
            *starter = *pointer_bus;
            *pointer_bus = temp;

            starter++;
        }
    }

    BusLine temp = *starter;
    *starter = *end;
    *end = temp;

    return starter;
}