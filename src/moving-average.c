#include <stdio.h>
#include <math.h>
#include "moving-average.h"

void moving_average_init(t_moving_average *tma, size_t size)
{
    tma->total = 0;
    tma->size = size;

    tma->ring_buffer = calloc(sizeof(int), size);
    tma->head = 0;
    tma->tail = 0;
    tma->is_full = 0;
}

int moving_average_push(t_moving_average *tma, int element)
{
    if (tma->is_full) {
        int popped = tma->ring_buffer[tma->head];
        tma->ring_buffer[tma->tail++] = element;
        tma->tail %= tma->size;

        /* head and tail are the same when it's full */
        tma->head = tma->tail;

        tma->total += -popped + element;

    } else {
        tma->ring_buffer[tma->tail++] = element;
        tma->tail %= tma->size;
        tma->total += element;

        printf("%d\n", tma->tail);

        /* head should be 0 until it's full. if tail has looped back to 0, this
         * push has filled the buffer */
        if (tma->tail == 0)
            tma->is_full = 1;
    }

    return moving_average_calc(tma);
}

int moving_average_calc(t_moving_average *tma)
{
    const size_t current_size = (tma->is_full) ? tma->size : (size_t)tma->tail;

    printf("current_size=%ld, total=%d\n", current_size, tma->total);
    if (current_size == 0)
        return 0;

    return ceil(tma->total / current_size);
}

void moving_average_reset(t_moving_average *tma)
{
    tma->head = 0;
    tma->tail = 0;
    tma->total = 0;
    tma->is_full = 0;
}
