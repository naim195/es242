#include <stdio.h>


typedef char board_t[15];

 
void print_board(board_t board) {
    for (int i = 0; i < 15; i++) {
        printf("%d ", board[i]);
    }
    printf("\n"); // Print a final newline for formatting
}
int board_sum(board_t board){
  int sum=0;
  for(int i=0;i<15;i++){
    sum+=board[i];
  }
  return sum;
}


int has_lost(board_t board, int player)
{
    int lost[20][3] = {{12,14,13}, {12,3,2}, {12,7,6}, {9,13,11}, {9,2,1}, {14,4,3}, {14,8,7}, {14,11,10}, {6,13,8}, {5,10,7}, {9,12,10}, {3,10,1}, {4,1,11}, {4,13,2}, {5,11,8}, {0,5,1}, {0,6,2}, {0,7,3}, {0,8,4}, {5,6,9}};
    
   
    for (int i = 0; i < 20; i++) {
        int j;
        for (j = 0; j < 3; j++) {
            if ( board[lost[i][j]] != player) {
              break;

            }
    
        }
        if (j == 3) {
          return 1; //  return 1 to indicate a valid move
        }
    }
 
    return 0;
}

int is_full(board_t board)
{   int sum=0;
    for (int i=0;i<15;i++){
        sum+=board[i];
    }
    if (sum==21){
        return 1;
    }
    return 0;
}

typedef struct {
    int player;
    int line; /* 0 for 12, 1 for 13, ..., 14 for 56. */
    int score; /* -1 for loss, 0 for draw, 1 for win. */
} move_t;

move_t best_move(board_t board, int player)
{  

    move_t candidate;
    move_t response;
    candidate.player=player;
    candidate.score=-1;


    // check if the sum of board is 21 meaning the last move is left so the t last player will definetly looss so directly retunn that player lost 
     if(board_sum(board)==21){
            // printf("################\n");
            // printf(" if ==14 \n");
            candidate.score=3-player;
            // printf(" candidate.score %d", candidate.score);
            // printf("\n#################\n");
     
            return candidate;
     }
    for (int i=0;i<15;i++){


// checking empty position on board and add the marker of the player
        if (board[i]==0){
            candidate.line=i;
            board[candidate.line]=player;
            // printf("i =%d",i);
            // printf(" board[i]=player");
            // print_board(board);
            // printf("\n");
// checking if the current player has host if made that move
            if (has_lost(board,player)){
                // printf("has lost  \nbefore :");
                // print_board(board);
// if lost clear that move n try another;
                board[i]=0;
                // printf("after :");
                // print_board(board);
                // printf("\n");

                continue;
            }
            // printf(" now response ");

            // #### checking the best move of another player and simulating it
            response=best_move(board,3-player);
            // printf("\n");
            // printf("count %d",count);
            // printf("\n");
            board[candidate.line]=0;
// ################ checking if player 2 lost it or not is yes the then the current player has its best move other wise change the move;
            if (response.player!=response.score){
                candidate.score=player;
                // printf("response.player!=response.score\n");
                board[candidate.line]=0;
                // printf("candidate.line %d",candidate.line);
                // printf("\n");

                // print_board(board);
                // printf("\n");

                return candidate;
            }

        }
        }

        // ##### this says that current player has no other possible postion availbe to make without loosing 
        candidate.score=3-player;
        // printf("after foor loop ends\nbefore :");
        // print_board(board);
        // printf("\n");
        board[candidate.line]=0;
        // printf("end :");
        // print_board(board);
        // printf("\n");
        return candidate;
    


    }




int main()
{
            // 1  2  3  4  5  6  7  8   9  10  11  12  13  14  15
  board_t board = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0};
  int human; 
//  ##################################################/#
  printf("please enter your Peference\n");
  printf("1 for player 1 and 2 for player 2\n");
  scanf("%d", &human );

  int computer = 3-human;
  int move_h; 
  if (human==1){
    // printf(" human ==1\n");
    while(!is_full(board) && !has_lost(board, human) && !has_lost(board, computer)){
    printf("please enter your move\n");
    scanf("%d", &move_h);
    if (board[move_h-1]!=0){
        printf("Enter valid move this board posistion is fulled \n");
        continue;
    }
    board[move_h-1]= human;

    // printf("current board condition\n");
    // print_board(b);

    printf("computers move\n");
    board[(best_move(board, computer)).line] = computer;

    printf("current board condition\n");
    print_board(board);
    printf("\n");
    }
  }



if (human==2){

    int var;
    while(!is_full(board) && !has_lost(board, human) && !has_lost(board, computer)){
    printf("computers move\n");
    var=(best_move(board, computer)).line;
    board[var] = computer;
    if (has_lost(board,computer)){
        break;
    }
    printf("\n");
    printf("please enter your move\n");
    scanf("%d", &move_h);
    if (board[move_h-1]!=0){
        printf("enter valid move\n");
        board[var]=0;
        // printf(" enter if \n");
        //  print_board(b);
        continue;
    }
    board[move_h-1]= human;

    // printf("current board condition\n");
    print_board(board);
    }
    printf("\n");
}

if (has_lost(board,human)){
  printf("You lose\n");
}
else{
printf(" You win\n");

}

  return 0;
}