#include <stdlib.h>

#ifndef _MOVING_AVERAGE_H_
#define _MOVING_AVERAGE_H_

typedef struct moving_average {
    int total;
    size_t size;

    int *ring_buffer;
    int head;
    int tail;

    int is_full;
} t_moving_average;


/**
 * Initialize t_moving_average instance
 *
 * @param tma t_moving_average instance
 * @param size Number of samples
 */
void moving_average_init(t_moving_average *tma, size_t size);

/**
 * Push element into moving average buffer, returns new average
 *
 * @param tma t_moving_average instance
 * @param element element to push into buffer
 */
int moving_average_push(t_moving_average *tma, int element);

/**
 * Calculate current moving average
 *
 * @param tma t_moving_average instance
 */
int moving_average_calc(t_moving_average *tma);

/**
 * Empty the moving average buffer
 *
 * @param tma t_moving_average instance
 */
void moving_average_reset(t_moving_average *tma);

#endif  /* _MOVING_AVERAGE_H_ */
