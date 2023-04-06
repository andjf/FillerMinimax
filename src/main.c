#include "board.h"
#include "point.h"
#include "minimax.h"
#include "queue.h"

int main(void)
{
    // Read the board from stdin
    struct board *b = create_board_from_stdin();
    // Display the board that we will perform minimax on
    print_board(b);
    printf("---------------\n");
    // Calculate and display the best color choice for this board
    printf("Best color choice: %c\n", color_to_char(best_color(b)));
    // Free the board after use
    free_board(b);
    return 0;
}