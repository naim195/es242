#include <stdio.h>
#include <assert.h>

typedef char board_t[4][5];
typedef char player_t;

enum {
    EMPTY = 0,
    RED = 1,
    BLUE = 2,
};

player_t switch_player(player_t player)
{
    switch (player) {
        case RED: return BLUE;
        case BLUE: return RED;
        default: assert(0);
    }
}

int has_won(board_t board, player_t player) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 2; col++) {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player) {
                return 1;
            }
  
        }
    }

    for (int col = 0; col < 5; col++) {
        for (int row = 0; row < 2; row++) {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player) {
                return 1;
            }
 
        }
    }

    for (int row = 0; row < 1; row++) {
        for (int col = 0; col < 2; col++) {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player) {
                return +10;
            }

        }
    }

    for (int row = 3; row >= 2; row--) {
        for (int col = 0; col < 2; col++) {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player) {
                return 1;
            }
        }
    }

    return 0;
}

int is_full(board_t board) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == EMPTY) {
                return 0;
            }
        }
    }
    return 1;
}

typedef struct {
    int col;
    int score;
} move_t;

int column_full(board_t board, int col)
{
    return board[0][col] != EMPTY;
}
int move_on_col(board_t board, int col, player_t player)
{
    for (int row = 3; row >= 0; row--) {
        if (board[row][col] == EMPTY) {
            board[row][col] = player;
            return row; 
        }
    }
    return -1; 
}

move_t best_move(board_t board, player_t player, int depth) {
    move_t bestMove;
    move_t tempMove = {-10, -10};
    int hasCandidate = 1;

    if (depth == 0 || is_full(board)) {
        tempMove.score = 0;
        return tempMove;
    }

    for (int col = 0; col < 5; ++col) {
        if (!column_full(board, col)) {
            int row = move_on_col(board, col, player);
            board[row][col] = player;
            if (has_won(board, player)) {
                board[row][col] = EMPTY;
                return (move_t){col, 10};
            }
            board[row][col] = EMPTY;
        }
    }
    
    for (int col = 0; col < 5; ++col) {
        if (!column_full(board, col)) {
            int row = move_on_col(board, col, player);
            board[row][col] = player;
            if (is_full(board)) {
                board[row][col] = EMPTY;
                return (move_t){col, 0};
            }
            tempMove = best_move(board, switch_player(player), depth - 1);
            board[row][col] = EMPTY;

            if (tempMove.score == -10) {
                return (move_t){col, 10};
            } else if (tempMove.score == 0) {
                bestMove = (move_t){col, 0};
                hasCandidate = 0;
            } else{
                if (hasCandidate) {
                    bestMove = (move_t){col, -10};
                    hasCandidate = 0;
                }
            }
        }
    }

    return bestMove;
}


void print_board(board_t board)
{
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 5; col++) {
            if (board[row][col] == EMPTY) {
                printf("0  ");
            } else if (board[row][col] == RED) {
                printf("R  ");
            } else if (board[row][col] == BLUE) {
                printf("B  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */
    int move, col;
    board_t board;
    move_t response;
    int x;
    printf("You are red colour, Do you choose to be player 1 or 2: ");
    scanf("%d", &x);
    player_t currentPlayer;

    if (x == 1) {
        currentPlayer = RED;
    } else if (x == 2) {
        currentPlayer = BLUE;
    } else {
        printf("\nInvalid choice");
        return 1; 
    }

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 5; col++) {
            board[row][col] = EMPTY;
        }
    }

    while (1) {
        if (x != 1 && x != 2) {
            printf("\nInvalid choice");
            break;
        }
        print_board(board);
        printf("\n\n");

        if (currentPlayer == RED) {
            printf("0  1  2  3  4\n");
            printf("\nEnter your move: ");
            scanf("%d", &move);
            col = move;

            if (col >= 0 && col < 5 && !column_full(board, col)) {
                move_on_col(board, col, currentPlayer);
            } else {
                printf("Invalid move. Try again.\n");
                continue;
            }
        } else {
            response = best_move(board, currentPlayer, 11);
            col = response.col;

            if (col >= 0 && col < 5 && !column_full(board, col)) {
                int row = move_on_col(board, col, currentPlayer);
            }
        }

        if (has_won(board, currentPlayer)) {
            print_board(board);
            printf("Player %c has won!\n", (currentPlayer == RED) ? 'R' : 'B');
            break;
        }else if (is_full(board)) {
            printf("It's a draw!\n");
            break;
        }

        currentPlayer = switch_player(currentPlayer);
    }
    return 0;
}