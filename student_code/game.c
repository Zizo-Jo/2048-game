#include "game.h"

/********************************************************/
/****************** Provided functions ******************/
/********************************************************/

void add_random_number(int board[MAX_ROWS][MAX_COLUMNS]){
	// Precompute all locations with 0s
    int rows[MAX_ROWS*MAX_COLUMNS];
    int cols[MAX_ROWS*MAX_COLUMNS];
    int total = 0;
    for(int r=0; r<MAX_ROWS; ++r){
        for(int c=0; c<MAX_COLUMNS; ++c){
            if(board[r][c] == 0){
                rows[total] = r;
                cols[total] = c;
                ++total;
            }
        }
    }
    // Select one of the 0 locations at random
    if(total > 0){
        int pos = rand()%total;
        // Add number 2 with 75% prob, or 4 with 25% prob.
        int value;
        if(rand()%4 == 0) value = 4;
        else value = 2;
        
        board[rows[pos]][cols[pos]] = value;
    }
}

void print_options(int board[MAX_ROWS][MAX_COLUMNS]){
    printf("Move options:\n");
    if(can_move_up(board))
        printf("\t%d. Move up\n", MOVE_UP);
    if(can_move_right(board))
        printf("\t%d. Move right\n", MOVE_RIGHT);
    if(can_move_down(board))
        printf("\t%d. Move down\n", MOVE_DOWN);
    if(can_move_left(board))
        printf("\t%d. Move left\n", MOVE_LEFT);
    printf("\t%d. Show best move\n", SHOW_BEST_MOVE);
    printf("\t%d. Quit game\n", QUIT_GAME);
}

void print_row(char start_symb, char end_symb, int n_cols){
    printf("%c", start_symb);
    for(int col=0; col<n_cols; ++col){
        printf("-----");
        if(col+1<n_cols) printf("+");
    }
    printf("%c\n", end_symb);
}

void print_board(int board[MAX_ROWS][MAX_COLUMNS]){
    // Before row
    print_row('/', '\\', MAX_COLUMNS);

    // Print each row
    for(int row=0; row<MAX_ROWS; ++row){
        for(int col=0; col<MAX_COLUMNS; ++col){
            if(board[row][col] > 0)
                printf("|%*d", 5, board[row][col]);
            else printf("|%*s", 5, "");
        }
        printf("|\n");
        if(row+1 < MAX_ROWS)
            print_row('|', '|', MAX_COLUMNS);
    }

    // After last row
    print_row('\\', '/', MAX_COLUMNS);
}

bool is_valid_option(int option, int board[MAX_ROWS][MAX_COLUMNS]){
    switch (option)
    {
    case MOVE_UP:
        return can_move_up(board);
    case MOVE_RIGHT:
        return can_move_right(board);
    case MOVE_DOWN:
        return can_move_down(board);
    case MOVE_LEFT:
        return can_move_left(board);
    case SHOW_BEST_MOVE:
        return true;
    case QUIT_GAME:
        return true;
    default:
        return false;
    }
}

int apply_move_option(int option, int board[MAX_COLUMNS][MAX_COLUMNS]){
    switch (option)
    {
    case MOVE_UP:
        return move_up(board);
    case MOVE_RIGHT:
        return move_right(board);
    case MOVE_DOWN:
        return move_down(board);
    case MOVE_LEFT:
        return move_left(board);
    }
    return 0;
}

/********************************************************/
/************* LAB 1 - functions to program *************/
/********************************************************/

bool is_goal(int board[MAX_ROWS][MAX_COLUMNS]){
    // @brief Computes whether the board is in a goal state
	// @Returns:
	// - true, if GOAL_VALUE is found in the board
	// - false, otherwise

    // Cheek the condition by a nested loop
    // And also denife the constant GOAL is 4 in the file "game.h"
    for(int i = 0;i<MAX_ROWS;i++){
        for(int j = 0;j<MAX_COLUMNS;j++){
            if (board[i][j] == GOAL){
                return true;
            }
        }
    }
    return false;
}

bool is_terminal(int board[MAX_ROWS][MAX_COLUMNS]){
	// @brief Computes whether the board is in a terminal state
	// @Returns:
	// - true, if the board is_goal or a valid move is no available
	// - false, otherwise

    // Cheek the condition by using the operators "||" (or),
    // Call the function "is_goal" and the functions relate "valid move"
    if ((is_goal(board)) || !(can_move_up(board) || can_move_down(board) || can_move_left(board) || can_move_right(board))){
        return true;
    }
    return false;
}

int move_right(int board[MAX_ROWS][MAX_COLUMNS]){
    // @brief Move all numbers in board to the RIGHT, 
    //        merging adjacent and equal values
    // @Returns the aggregated score of all merged values
    
    // Declare a varieble score to compute the score of game, 
    // it returns the scores that player obtained in this turn,
    // and it returns the changed board
    int score = 0;
    
    // We build a nested loop, 
    // the first loop is for cheeking numbers from the top to the bottom,(rows)
    // the scond loop is for cheeking numbers from the right to the left,(columne)
    // the third loop is for operating the numbers,(changes numbers and compute score)

    for (int i = 0; i < MAX_ROWS; i++){
        // Declare a varieble called ranges to avoid counting all numbers in the columne at once
        int ranges = 0;
        for (int j = (MAX_COLUMNS - 2); j >= 0; j--){
            if (board[i][j] != 0){
                for (int k = (j + 1); k < (MAX_ROWS - ranges); k++){
                    if (board[i][k] == board[i][j]){
                        board[i][k] += board[i][j];
                        board[i][j] = 0;
                        score += board[i][k];
                        ranges = (MAX_ROWS - k);
                        break;
                    }
                    else if (board[i][k] != 0){
                        board[i][k-1] = board[i][j];
                        if ((k-1) != j) {
                            board[i][j] = 0;
                        }
                        break;
                    }
                    else if (k == (MAX_ROWS - 1) - ranges){
                        board[i][k] = board[i][j];
                        board[i][j] = 0;
                        break;
                    }            
                }
            }
            
        }
    }
    return score;
}

int move_left(int board[MAX_ROWS][MAX_COLUMNS]){
    // @brief Move all numbers in board to the LEFT, 
    //        merging adjacent and equal values
    // @Returns the aggregated score of all merged values

    // Declare a varieble score to compute the score of game, 
    // it returns the scores that player obtained in this turn,
    // and it returns the board changed
    int score = 0;
    
    // We build a nested loop, 
    // the first loop is for cheeking numbers from the top to the bottom,(rows)
    // the scond loop is for cheeking numbers from the left to the right,(columne)
    // the third loop is for operating the numbers,(changes numbers and compute score)

    for (int i = 0; i < MAX_ROWS; i++){
        // Declare a varieble called ranges to avoid counting all numbers in the columne at once
        int ranges = 0;
        for (int j = (MAX_COLUMNS - 3); j < MAX_COLUMNS; j++){
            if (board[i][j] != 0){
                for (int k = (j - 1); k > (ranges - 1); k--){
                    if (board[i][k] == board[i][j]){
                        board[i][k] += board[i][j];
                        board[i][j] = 0;
                        score += board[i][k];
                        ranges = (k+1);
                        break;
                    }
                    else if (board[i][k] != 0){
                        board[i][k+1] = board[i][j];
                        if ((k+1) != j) {
                            board[i][j] = 0;
                        }
                        break;
                    }
                    else if (k == 0 + ranges){
                        board[i][k] = board[i][j];
                        board[i][j] = 0;
                        break;
                    }               
                }
            }
            
        }
    }
    return score;
}

int move_up(int board[MAX_ROWS][MAX_COLUMNS]){
    // @brief Move all numbers in board to the UP, 
    //        merging adjacent and equal values
    // @Returns the aggregated score of all merged values

    // Declare a varieble score to compute the score of game, 
    // it returns the scores that player obtained in this turn,
    // and it returns the changed board
    int score = 0;

    // We build a nested loop, 
    // the first loop is for cheeking numbers from the left to the right,(columns)
    // the scond loop is for cheeking numbers from the top to the bottom,(rows)
    // the third loop is for operating the numbers,(changes numbers and compute score)

    for (int i = 0; i < MAX_COLUMNS; i++){
        // Declare a varieble called ranges to avoid counting all numbers in the columne at once
        int ranges = 0;
        for (int j = (MAX_ROWS - 3); j < MAX_ROWS; j++){
            if (board[j][i] != 0){
                for (int k = (j - 1); k > (ranges - 1); k--){
                    if (board[k][i] == board[j][i]){
                        board[k][i] += board[j][i];
                        board[j][i] = 0;
                        score += board[k][i];
                        ranges = (k+1);
                        break;
                    }
                    else if (board[k][i] != 0){
                        board[k+1][i] = board[j][i];
                        if ((k+1) != j) {
                            board[j][i] = 0;
                        }
                        break;
                    }
                    else if (k == 0 + ranges){
                        board[k][i] = board[j][i];
                        board[j][i] = 0;
                        break;
                    }
                }
            }

        }
    }
    return score;
}

int move_down(int board[MAX_ROWS][MAX_COLUMNS]){
    // @brief Move all numbers in board to the DOWN, 
    //        merging adjacent and equal values
    // @Returns the aggregated score of all merged values

    // Declare a varieble score to compute the score of game, 
    // it returns the scores that player obtained in this turn,
    // and it returns the changed board
    int score = 0;
    
    // We build a nested loop, 
    // the first loop is for cheeking numbers from the left to the right,(columns)
    // the scond loop is for cheeking numbers from the bottom to the top,(rows)
    // the third loop is for operating the numbers,(changes numbers and compute score)

    for (int i = 0; i < MAX_COLUMNS; i++){
        // Declare a varieble called ranges to avoid counting all numbers in the columne at once
        int ranges = 0;
        for (int j = (MAX_ROWS - 2); j >= 0; j--){
            if (board[j][i] != 0){
                for (int k = (j + 1); k < (MAX_ROWS - ranges); k++){
                    if (board[k][i] == board[j][i]){
                        board[k][i] += board[j][i];
                        board[j][i] = 0;
                        score += board[k][i];
                        ranges = (MAX_ROWS - k);
                        break;
                    }
                    else if (board[k][i] != 0){
                        board[k-1][i] = board[j][i];
                        if ((k-1) != j) {
                            board[j][i] = 0;
                        }
                        break;
                    }
                    else if (k == (MAX_ROWS - 1) - ranges){
                        board[k][i] = board[j][i];
                        board[j][i] = 0;
                        break;
                    }            
                }
            }
            
        }
    }
    return score;
}

bool can_move_up(int board[MAX_ROWS][MAX_COLUMNS]){
    // @brief Computes whether the UP move is available for the given board
    // @Returns:
    // - true, if UP move would change the board,
    // - false, otherwise

    // Traverse each column
    for (int j = 0; j < MAX_COLUMNS; j++){
        // Select top value for comparisons
        int check_value = board[MAX_ROWS - 1][j];
        for (int i = MAX_ROWS - 2; i > -1; i--){
            if (check_value != 0){
                if (board[i][j] == 0){
                    // For a given non-zero value, check if there's space below
                    return true;
                }
                else if (board[i][j] == check_value){
                    // Check if there's equivalent value 
                    return true;
                }  
            }

            if (check_value == 0 || check_value != board[i][j]) {
                check_value = board[i][j];
            }
        }
    }
    return false;
}

bool can_move_right(int board[MAX_ROWS][MAX_COLUMNS]){   
    // @brief Computes whether the RIGHT move is available for the given board
    // @Returns:
    // - true, if RIGHT move would change the board,
    // - false, otherwise

    // Traverse each row
    for (int i = 0; i < MAX_ROWS; i++){
        // Select first value for comparisons
        int check_value = board[i][0];
        for (int j = 1; j < MAX_COLUMNS; j++){
            if (check_value != 0){
                // If selected value is a number and not empty (0)
                if (board[i][j] == 0){
                    // Checks if there is empty space at the right
                    return true;
                }
                else if (board[i][j] == check_value){
                    // Checks if there's value that can be added together
                    return true;
                }  
            }

            // Update value to continue comparing to the right
            if (check_value == 0 || check_value != board[i][j]) {
                check_value = board[i][j];
            }
        }
    }

    return false;
}

bool can_move_down(int board[MAX_ROWS][MAX_COLUMNS]){
    // @brief Computes whether the DOWN move is available for the given board
    // @Returns:
    // - true, if DOWN move would change the board,
    // - false, otherwise

    // Same logic as moving right
    // Traverse for each row, traverse its column
    // Check if for a given non-zero value there's an empty space below it
    // Or if there's an equivalent value
    // Else return false
    for (int j = 0; j < MAX_COLUMNS; j++){
        int check_value = board[0][j];
        for (int i = 1; i < MAX_ROWS; i++){
            if (check_value != 0){
                if (board[i][j] == 0){
                    return true;
                }
                else if (board[i][j] == check_value){
                    return true;
                }
            }

            if (check_value == 0 || check_value != board[i][j]) {
                check_value = board[i][j];
            }
        }
    }
    return false;
}

bool can_move_left(int board[MAX_ROWS][MAX_COLUMNS]){
    // @brief Computes whether the LEFT move is available for the given board
    // @Returns:
    // - true, if LEFT move would change the board,
    // - false, otherwise

    for (int i = 0; i < MAX_ROWS; i++){
        // Select a value to compare with the rest of the column
        // Right-most value
        int check_value = board[i][MAX_COLUMNS-1];
        // Check from right to left
        for (int j = MAX_COLUMNS - 2; j > -1; j--){
            if (check_value != 0){
                if (board[i][j] == 0){
                    return true;
                }
                else if (board[i][j] == check_value){
                    return true;
                }
            }

            // Update value if they are not the same as selected value or if it is zero
            if (check_value == 0 || check_value != board[i][j]) {
                check_value = board[i][j];
            }
        }
    }
    return false;
}