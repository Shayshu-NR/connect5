#include <stdlib.h>

/*~~~~~Function Prototypes */
char** board_set_up(int x, int y);
void destroy_board(char **board);
/*~~~~~~~~~~~~~~~~~~~~~~~ */


int main(void){
    char** board = board_set_up(7, 8);
    
    destroy_board(board);
    return 0;
}



//Sets up the intial board data structure and sets
//each entry to empty ('e')
char** board_set_up(int x, int y){
    char** initial_board = malloc(x * sizeof(char*));

    for(int i = 0; i < x; i++){
        initial_board[i] = malloc(y * sizeof(char*));
    }

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            initial_board[i][j] = 'e';
        }
    }

    return initial_board;
}

//Deallocates the board data structure
void destroy_board(char **board){
    free(*board);
    free(**board);

    return;
}