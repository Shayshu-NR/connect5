#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/*~~~~~Function Prototypes */
char** board_set_up(int y, int x);
void destroy_board(char **board);
bool check_legal(int potential_col, char **board, int y, int x);
char** update_game_board(int user_move, char **board, int y, char turn);
void print_board(char **board);
/*~~~~~~~~~~~~~~~~~~~~~~~ */


int main(void){
    char** board = board_set_up(7, 8);


    destroy_board(board);
    return 0;
}

/*~~~~~Functions~~~~~*/
//Sets up the intial board data structure and sets
//each entry to empty ('e')
char** board_set_up(int y, int x){
    char** initial_board = malloc(y * sizeof(char*));

    for(int i = 0; i < y; i++){
        initial_board[i] = malloc(x * sizeof(char*));
    }

    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){

            //'e' means the spot is empty  
            initial_board[i][j] = 'e';
        }
    }

    return initial_board;
}


//De-allocates the board data structure
void destroy_board(char **board){
    free(*board);
    free(board);

    return;
}


//Checks if the user is alloowed to place their
//token into a given column, returns true if the move is valid
bool check_legal(int potential_col, char **board, int y, int x){
    //Check the column for any open spaces
    for(int i = 0; i < y; i++){
        if(board[i][potential_col] == 'e'){
            return true;
        }
    }

    //If there are no open spaces in a column then return false
    return false;
}


//Updates the game board for a given user input
char** update_game_board(int user_move, char **board, int y, char turn){

    for(int i = y - 1; i >= 0; i--){
        if(board[i][user_move] == 'e'){
            board[i][user_move] = turn;
            return board;
        }
    }

    return board;
}


//Prints the board to the terminal, for debugging
void print_board(char **board){
  for(int i = 0; i < 7; i++){
      for(int j = 0;  j <  8; j++){
        printf("%c ", board[i][j]);
      } 
      printf("\n");
    }
    printf("\n\n");
}
/*~~~~~~~~~~~~~~~~~~~*/