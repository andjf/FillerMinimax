#ifndef MINIMAX_H
#define MINIMAX_H

#include <inttypes.h>
#include <stdbool.h>

#include "board.h"
// #include "point.h"

int8_t minimax(struct board *b, int8_t depth, bool maximizing_player);

int8_t best_color(struct board *b, int8_t max_depth);

#endif