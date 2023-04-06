#include "point.h"

point create_point(int8_t x, int8_t y)
{
    return y * W + x;
}

int8_t get_x(point p)
{
    return p % W;
}

int8_t get_y(point p)
{
    return p / W;
}

point up_rows(point p, int8_t num_rows)
{
    // assert(p - (W * num_rows) >= 0);
    return p - (W * num_rows);
}

point down_rows(point p, int8_t num_rows)
{
    // assert(p + (W * num_rows) < W * H);
    return p + (W * num_rows);
}

point left_cols(point p, int8_t num_cols)
{
    // assert(get_x(p) - num_cols >= 0);
    return get_x(p) - num_cols >= 0 ? p - num_cols : -1;
}

point right_cols(point p, int8_t num_cols)
{
    // assert(get_x(p) + num_cols < W);
    return get_x(p) + num_cols < W ? p + num_cols : -1;
}

bool on_board(point p)
{
    return p >= 0 && p < W * H;
    // int8_t x = get_x(p);
    // int8_t y = get_y(p);
    // return (x >= 0 && x < W) && (y >= 0 && y < H);
}
