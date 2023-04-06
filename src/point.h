#ifndef POINT_H
#define POINT_H

#include <inttypes.h>
#include <stdbool.h>

typedef int8_t point;

#include "board.h"

point create_point(int8_t x, int8_t y);

int8_t get_x(point p);

int8_t get_y(point p);

point up_rows(point p, int8_t num_rows);

point down_rows(point p, int8_t num_rows);

point left_cols(point p, int8_t num_cols);

point right_cols(point p, int8_t num_cols);

bool on_board(point p);

#endif