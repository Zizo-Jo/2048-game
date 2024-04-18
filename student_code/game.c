#include "game.h"


/********************************************************/
/****************** Provided functions ******************/
/********************************************************/

void add_random_number(int board[MAX_ROWS][MAX_COLUMNS]){
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
    
    if(total > 0){
        int pos = rand()%total;
        // 75% -> 2; 25% -> 4
        int value;
        if(rand()%4 == 0) value = 4;
        else value = 2;
        printf("Added number %d at (%d,%d)\n", value, rows[pos], cols[pos] );
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

/********************************************************/
/************* LAB 2 - functions to program *************/
/********************************************************/

void init_game_state(GameState *game_state){
    // @brief Set the game state score and all board cells to 0, and
    //        adds the number 2 in two random cells of the board
    // @Returns: nothing

    // Sets board values to 0
    for (int i = 0; i < MAX_ROWS; i++){
        for (int j = 0; j < MAX_COLUMNS; j++){
            game_state->board[i][j] = 0;
        }
    }
    // Sets scores to zero
    game_state->score = 0;

    // Adds two random numbers
    add_random_number(game_state->board);
    add_random_number(game_state->board);
}


void print_game_state(GameState* game_state){
    // @brief Prints the game state score and board on the screen
    // @Returns: nothing

    printf("Score: %d\n", game_state->score);
    // Pass board array to print_board function
    printf("\n");
    print_board(game_state->board);
}


/********************************************************/
/************* LAB 3 - functions to program *************/
/********************************************************/

GameState* make_game_state(){
    // @brief Allocates memory for a GameState and returns 
    //        its address
    // @Returns: a pointer to a new GameState
    GameState* new_game_state = malloc(sizeof(*new_game_state));
    return new_game_state;
}

GameState* copy(GameState *game_state){
    // @brief Makes a new game state in which all data from 
    //        game_state is copied, then returns the new address
    // @Returns: a pointer to a new GameState
    GameState* new_game_state = malloc(sizeof(*new_game_state));
    new_game_state->score = game_state->score;
    for (int i = 0; i < MAX_ROWS; i++){
        for (int j = 0; j < MAX_COLUMNS; j++){
            new_game_state->board[i][j] = game_state->board[i][j];
        }
    }
    return new_game_state;
}

void free_game_state(GameState *game_state){
    // @brief Frees the game_state memory if it is not NULL
    // @Returns: nothing
    if (game_state != NULL){
        free(game_state);
    }
}


/********************************************************/
/************* LAB 4 - functions to program *************/
/********************************************************/

int recursive_best_score(GameState *game_state, int depth){
	// @brief Returns the game_state score if depth is 0 or the game
	//        state is terminal, otherwise makes MAX_REPETITIONS 
	//        recursive calls for every valid move. 
	// @Returns: the max aggregated score found among all function calls
	
	// 0. set the best score to the current game state score
	
	// 1. Implement base cases (return the best score)
	
	// 2. For every valid option run:
	//     - set an integer aggregated_score to 0
	//     - run MAX_REPETITIONS times the following steps:
	//       - 2.a, copy the game_state
	//       - 2.b, apply the valid option to the copied board and
	//              increase copied game state score
	//       - 2.c, add to aggregated_score the result of the 
	//              recursive call with the current option and depth-1
	//       - 2.d, free the copied game
	//     - set the best_score to the max value between best_score
	//       and the aggregated_score
	
	// 3. Return the best score
    int best_score = game_state->score;

    if (depth <= 0 || is_terminal(game_state->board)){
        return best_score;
    }

    int moves[] = {MOVE_UP, MOVE_DOWN, MOVE_RIGHT, MOVE_LEFT};

    for (int i = 0; i < sizeof(moves)/sizeof(moves[0]); i++){
        int aggregated_score = 0;
        if (is_valid_option(moves[i], game_state->board)){
            for (int j = 0; j < MAX_REPETITIONS; j++){
                GameState *copy_state = malloc(sizeof(GameState));
                *copy_state = *game_state; 
                copy_state->score += apply_move_option(moves[i], copy_state->board);
                aggregated_score = copy_state->score + recursive_best_score(copy_state, depth-1);
                free(copy_state);
            }
            best_score = max(aggregated_score, best_score);
        }
    }

    return best_score;

}

int show_best_move(GameState *game_state){
	// @brief For every valid option (move), runs MAX_REPETITIONS 
	//        recursive_best_score calls for the resulting game state
	//        after applying the move and MAX_DEPTH. The outcome of 
	//        the recursive call is aggregated to the total score for
	//        that move, and if it is better than the best score so far, 
	//        the total score is saved as the best one. At the end, the best move
	//        is printed on screen and returned.
	// @Returns: the integer identifier of the best move
    
    int best_score = 0;
    int best_move = 0;
    
    int moves[] = {MOVE_UP, MOVE_DOWN, MOVE_RIGHT, MOVE_LEFT};
    for (int i = 0; i < sizeof(moves)/sizeof(moves[0]); i++){
        int total_score = 0;
        if (is_valid_option(moves[i], game_state->board)){
            for (int j = 0; j < MAX_REPETITIONS; j++){
                GameState *copy_state = malloc(sizeof(GameState));
                *copy_state = *game_state; 
                copy_state->score += apply_move_option(moves[i], copy_state->board);
                total_score = copy_state->score + recursive_best_score(copy_state, MAX_DEPTH);
                free(copy_state);
            }
            if (total_score > best_score){
                best_score = total_score;
                best_move = moves[i];
            }
        }
    }
    switch(best_move){
        case MOVE_UP:
            printf("Best move is UP. Expected score: %d\n", best_score/MAX_REPETITIONS);
            break;
        case MOVE_RIGHT:
            printf("Best move is RIGHT. Expected score: %d\n", best_score/MAX_REPETITIONS);
            break;
        case MOVE_DOWN:
            printf("Best move is DOWN. Expected score: %d\n", best_score/MAX_REPETITIONS);
            break;
        case MOVE_LEFT:
            printf("Best move is LEFT. Expected score: %d\n", best_score/MAX_REPETITIONS);
            break;
    }
    return best_move;
}

