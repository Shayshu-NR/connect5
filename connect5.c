#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/*~~~~~Function Prototypes~~~~~*/
char** board_set_up(int y, int x);
void destroy_board(char **board);
bool check_legal(int potential_col, char **board, int y, int x);
char** update_game_board(int user_move, char **board, int y, char turn);
bool check_win_state(char ** board, int y, int x);
void print_board(char **board);
/*~~~~~~~~~~~~~~~~~~~~~~~ */


int main(void){
    char** board = board_set_up(7, 8);
    char turn = 'r';

    while(!check_win_state(board, 7, 8)){
        print_board(board);

        int col_Select;
        
        printf("Move ");
        scanf("%d", &col_Select);

        while(!check_legal(col_Select, board, 7, 8)){
            printf("Move ");
            scanf("%d", &col_Select);
        }

        update_game_board(col_Select, board, 7, turn);

        if(turn == 'r'){
            turn = 'y';
        }
        else{
            turn = 'r';
        }
    }

    print_board(board);
    printf("Winner!");


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
            initial_board[i][j] = 'o';
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


//Checks the win state of the board and returns true or false
bool check_win_state(char ** board, int y, int x){
    int count_red = 0;
    int count_yellow = 0;

    //Check horizonal cases
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            //Check for red
            if(board[i][j] == 'r'){
                count_red++;
            }
            else{
                count_red = 0;
            }
            
            //Check for yellow
            if(board[i][j] == 'y'){
                count_yellow++;
            }
            else{
                count_yellow = 0;
            }

            if(count_red >= 5 || count_yellow >= 5){
                return true;
            }
        }
    }

    //Reset counter
    count_red = 0;
    count_yellow = 0;

    //Check vertical cases
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            //Check for red
            if(board[j][i] == 'r'){
                count_red++;
            }
            else{
                count_red = 0;
            }
            
            //Check for yellow
            if(board[j][i] == 'y'){
                count_yellow++;
            }
            else{
                count_yellow = 0;
            }

            if(count_red >= 5 || count_yellow >= 5){
                return true;
            }
        }
    }

    //Reset counter
    count_red = 0;
    count_yellow = 0;
    
    //Check diagonal cases
    //Case 1: top left to bottom right lower half
    for(int diagStart = 0; diagStart < 3; diagStart++){
        
        int row, col;
        for(row = diagStart, col = 0; row < y && col < x; row++, col++){
            //Check for red
            if(board[row][col] == 'r'){
                count_red++;
            }
            else{
                count_red = 0;
            }
            
            //Check for yellow
            if(board[row][col] == 'y'){
                count_yellow++;
            }
            else{
                count_yellow = 0;
            }

            if(count_red >= 5 || count_yellow >= 5){
                return true;
            }
        }
    }

    //Reset counter
    count_red = 0;
    count_yellow = 0;

    //Case 2: top left to bottom right upper half
    for(int diagStart = 1; diagStart < 4; diagStart++){

        int row, col;
        for(row = 0, col = diagStart; row < y && col < x; row++, col++){
            //Check for red
            if(board[row][col] == 'r'){
                count_red++;
            }
            else{
                count_red = 0;
            }
            
            //Check for yellow
            if(board[row][col] == 'y'){
                count_yellow++;
            }
            else{
                count_yellow = 0;
            }

            if(count_red >= 5 || count_yellow >= 5){
                return true;
            }
        }
    }

    //Reset counter
    count_red = 0;
    count_yellow = 0;

    //Case 3: top right to bottom left lower half
    for(int diagStart = 0; diagStart > 3; diagStart--){

        int row, col;
        for(row = diagStart, col = x - 1; row < y  && col > 0; row++, col--){
            //Check for red
            if(board[row][col] == 'r'){
                count_red++;
            }
            else{
                count_red = 0;
            }
            
            //Check for yellow
            if(board[row][col] == 'y'){
                count_yellow++;
            }
            else{
                count_yellow = 0;
            }

            if(count_red >= 5 || count_yellow >= 5){
                return true;
            }
        }
    }

    //Reset counter
    count_red = 0;
    count_yellow = 0;

    //Case 4: top right to bottom left upper half
    for(int diagStart = 6; diagStart > 3; diagStart--){

        int row, col;
        for(row = 0, col = diagStart; row > y && col > 0; row++, col--){
            //Check for red
            if(board[row][col] == 'r'){
                count_red++;
            }
            else{
                count_red = 0;
            }
            
            //Check for yellow
            if(board[row][col] == 'y'){
                count_yellow++;
            }
            else{
                count_yellow = 0;
            }

            if(count_red >= 5 || count_yellow >= 5){
                return true;
            }
        }
    }
    return false;
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