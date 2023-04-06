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

void *run_minimax(void *board)
{
    int8_t *score = malloc(sizeof(int8_t));
    *score = minimax((struct board *)board, MAX_DEPTH, true);
    return score;
}

int8_t best_color(struct board *b)
{
    pthread_t threads[4];
    struct board *boards[4];
    int8_t colors[4];
    int8_t thread_index = 0;
    for (int8_t color = 0, options = next_colors(b); color < 6; color++, options >>= 1)
    {
        if (options & 1)
        {
            boards[thread_index] = apply_move(b, color, true);
            colors[thread_index] = color;
            pthread_create(threads + thread_index, NULL, run_minimax, boards[thread_index]);
            thread_index++;
        }
    }

    int8_t max_score = -1;
    int8_t max_color = -1;
    for (int i = 0; i < thread_index; i++)
    {
        void *score_void;
        pthread_join(threads[i], &score_void);

        int8_t score = *((int8_t *)score_void);
        free(score_void);
        printf("Thread %ld reported a score of %d with color %c\n", threads[i], score, color_to_char(colors[i]));
        if (max_score == -1 || score > max_score)
        {
            max_score = score;
            max_color = colors[i];
        }
        free_board(boards[i]);
    }

    return max_color;
}
