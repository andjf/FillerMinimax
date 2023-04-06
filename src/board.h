#ifndef BOARD_H
#define BOARD_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "point.h"
#include "queue.h"

#define RED 0
#define YELLOW 1
#define GREEN 2
#define BLUE 3
#define PURPLE 4
#define BLACK 5

#define W 8
#define H 7

struct board
{
    int8_t data[W * H];
};

int8_t char_to_color(char c);

char color_to_char(int8_t color);

struct board *create_board_from_stdin();

void print_board(struct board *b);

void free_board(struct board *b);

int8_t color_at(struct board *b, point p);

struct board *board_copy(struct board *b);

int8_t score_position(struct board *b, point p);

int8_t score(struct board *b);

bool is_terminal(struct board *b);

int8_t next_colors(struct board *b);

struct board *apply_move(struct board *b, int8_t color, bool bottom_left);

#endif