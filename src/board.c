#include "board.h"

/*
RED    0
YELLOW 1
GREEN  2
BLUE   3
PURPLE 4
BLACK  5
*/
int8_t char_to_color(char c)
{
    switch (c)
    {
    case 'R':
        return RED;
    case 'Y':
        return YELLOW;
    case 'G':
        return GREEN;
    case 'B':
        return BLUE;
    case 'P':
        return PURPLE;
    case 'K':
        return BLACK;
    default:
        return -1;
    }
}

char color_to_char(int8_t color)
{
    return "RYGBPK"[color];
}

struct board *create_board_from_stdin()
{
    struct board *b = calloc(1, sizeof(struct board));
    char buffer[10];
    for (int8_t y = 0; y < H; y++)
    {
        assert(scanf("%8s\n", buffer) == 1);
        for (int8_t x = 0; x < W; x++)
        {
            int8_t color = char_to_color(buffer[x]);
            assert(color >= RED && color <= BLACK);
            b->data[y * W + x] = color;
        }
    }
    return b;
}

void print_board(struct board *b)
{
    for (int8_t y = 0; y < H; y++)
    {
        for (int8_t x = 0; x < W; x++)
        {
            printf("%c", color_to_char(b->data[y * W + x]));
            if (x < W - 1)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void free_board(struct board *b)
{
    free(b);
}

int8_t color_at(struct board *b, point p)
{
    return b->data[p];
}

struct board *board_copy(struct board *b)
{
    struct board *copy = calloc(1, sizeof(struct board));
    for (int8_t i = 0; i < W * H; i++)
        copy->data[i] = b->data[i];
    return copy;
}

int8_t score_position(struct board *b, point p)
{
    // The color of the starting point of the flood fill
    int8_t original_color = color_at(b, p);
    // The number of cells that have been filled
    int8_t num_explored_cells = 0;
    // Keep track of what cells have been seen
    bool seen[W * H] = {false};
    // Queue to keep track of which cells to explore
    struct Queue *q = create_queue();
    // Enqueue the first point
    enqueue(q, p);
    // While there are more points to explore...
    while (size(q))
    {
        // Get the current point
        point curr_p = dequeue(q);
        // If we've already seen it, skip
        if (seen[curr_p])
            continue;

        // Count the cell as being filled
        num_explored_cells++;
        // Record visiting this cell
        seen[curr_p] = true;

        // Check UP
        point up = up_rows(curr_p, 1);
        if (on_board(up) && color_at(b, up) == original_color)
            enqueue(q, up);

        // Check DOWN
        point down = down_rows(curr_p, 1);
        if (on_board(down) && color_at(b, down) == original_color)
            enqueue(q, down);

        // Check LEFT
        point left = left_cols(curr_p, 1);
        if (on_board(left) && color_at(b, left) == original_color)
            enqueue(q, left);

        // Check RIGHT
        point right = right_cols(curr_p, 1);
        if (on_board(right) && color_at(b, right) == original_color)
            enqueue(q, right);
    }

    // free the queue
    free_queue(q);

    return num_explored_cells;
}

/*
2333...3332
3444...4443
3444 . 4443
3444 . 4443
3444 . 4443
3444...4443
2333...3332

Total possible size of the queue during DFS:
(4 * (w - 2) * (h - 2)) + (3 * 2 * ((w - 2) + (h - 2))) + (2 * 4)

For a (w, h) = (8, 7) => 194
*/
int8_t score(struct board *b)
{
    return score_position(b, create_point(0, H - 1)) - score_position(b, create_point(W - 1, 0));
}

bool is_terminal(struct board *b)
{
    return (score_position(b, create_point(0, H - 1)) + score_position(b, create_point(W - 1, 0))) == (W * H);
}

// Returns a single byte that represents a dense bool
// signifying what colors could be used in the form:
//     --KP BGYR
//       54 3210
int8_t next_colors(struct board *b)
{
    int8_t possible_colors = 0x3F; // 0011 1111
    possible_colors ^= (1 << color_at(b, create_point(0, H - 1)));
    possible_colors ^= (1 << color_at(b, create_point(W - 1, 0)));
    // the two corners should never have the same color.
    // Therefore, they will not flip the same bit position.
    return possible_colors;
}

struct board *apply_move(struct board *b, int8_t color, bool bottom_left)
{
    struct board *new_board = board_copy(b);
    point start_point = create_point(bottom_left ? 0 : W - 1, bottom_left ? H - 1 : 0);
    int8_t original_color = color_at(new_board, start_point);

    // Keep track of what cells have been seen
    bool seen[W * H] = {false};
    // Queue to keep track of which cells to explore
    struct Queue *q = create_queue();
    // Enqueue the first point
    enqueue(q, start_point);
    // While there are more points to explore...
    while (size(q))
    {
        // Get the current point
        point curr_p = dequeue(q);
        // If we've already seen it, skip
        if (seen[curr_p])
            continue;

        // Record visiting this cell
        seen[curr_p] = true;

        new_board->data[get_y(curr_p) * W + get_x(curr_p)] = color;

        // Check UP
        point up = up_rows(curr_p, 1);
        if (on_board(up) && color_at(b, up) == original_color)
            enqueue(q, up);

        // Check DOWN
        point down = down_rows(curr_p, 1);
        if (on_board(down) && color_at(b, down) == original_color)
            enqueue(q, down);

        // Check LEFT
        point left = left_cols(curr_p, 1);
        if (on_board(left) && color_at(b, left) == original_color)
            enqueue(q, left);

        // Check RIGHT
        point right = right_cols(curr_p, 1);
        if (on_board(right) && color_at(b, right) == original_color)
            enqueue(q, right);
    }

    // free the queue
    free_queue(q);

    return new_board;
}
