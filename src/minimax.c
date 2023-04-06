#include "minimax.h"

int8_t minimax(struct board *b, int8_t depth, bool maximizing_player)
{
    if (depth == 0 || is_terminal(b))
    {
        return score(b);
    }

    if (maximizing_player)
    {
        int8_t max_score = -1;
        for (int8_t color = 0, options = next_colors(b); color < 6; color++, options >>= 1)
        {
            if (options & 1)
            {
                struct board *new_board = apply_move(b, color, true);
                int8_t score = minimax(new_board, depth - 1, false);
                free_board(new_board);
                if (max_score == -1 || score > max_score)
                    max_score = score;
            }
        }
        return max_score;
    }
    else
    {
        int8_t min_score = 2 * (W * H);
        for (int8_t color = 0, options = next_colors(b); color < 6; color++, options >>= 1)
        {
            if (options & 1)
            {
                struct board *new_board = apply_move(b, color, false);
                int8_t score = minimax(new_board, depth - 1, true);
                free_board(new_board);
                if (min_score == 2 * (W * H) || score < min_score)
                    min_score = score;
            }
        }
        return min_score;
    }
}

int8_t best_color(struct board *b, int8_t max_depth)
{
    int8_t max_score = -1;
    int8_t max_color = -1;
    for (int8_t color = 0, options = next_colors(b); color < 6; color++, options >>= 1)
    {
        if (options & 1)
        {
            struct board *new_board = apply_move(b, color, true);
            int8_t score = minimax(new_board, max_depth, true);
            free_board(new_board);
            if (max_score == -1 || score > max_score)
            {
                max_score = score;
                max_color = color;
            }
        }
    }
    return max_color;
}
