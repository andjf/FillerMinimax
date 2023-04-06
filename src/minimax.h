#ifndef MINIMAX_H
#define MINIMAX_H

#define MAX_DEPTH 10

#include <inttypes.h>
#include <stdbool.h>
#include <pthread.h>

#include "board.h"
#include "point.h"

int8_t minimax(struct board *b, int8_t depth, bool maximizing_player);

int8_t best_color(struct board *b);

#endif