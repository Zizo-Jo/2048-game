#ifndef _GAME_H_
#define _GAME_H_

#include "common.h"
#include "utils.h"

/// LAB 1 - macros
#define MAX_ROWS 4
#define MAX_COLUMNS 4
#define GOAL 2048

/// LAB 4 - macros 
#define MAX_DEPTH 4
#define MAX_REPETITIONS 4

/// LAB 2 - data structure
typedef struct{
    int score;
    int board[MAX_ROWS][MAX_COLUMNS];
}GameState;

/// LAB 4 - function
int recursive_best_score(GameState *game_state, int depth);

int show_best_move(GameState *game_state);


/// LAB 3 - functions
GameState* make_game_state();

GameState* copy(GameState *game_state);

void free_game_state(GameState *game_state);


/// LAB 2 - functions
void init_game_state(GameState *game_state);

void print_game_state(GameState* game_state);


/// LAB 1 - given functions
void add_random_number(int board[MAX_ROWS][MAX_COLUMNS]);

void print_row(char start_symb, char end_symb, int n_cols);

void print_options(int board[MAX_ROWS][MAX_COLUMNS]);

void print_board(int board[MAX_ROWS][MAX_COLUMNS]);

bool is_valid_option(int option, int board[MAX_ROWS][MAX_COLUMNS]);

/// LAB 1 - functions
bool is_goal(int board[MAX_ROWS][MAX_COLUMNS]);

bool is_terminal(int board[MAX_ROWS][MAX_COLUMNS]);

int move_right(int board[MAX_ROWS][MAX_COLUMNS]);

int move_left(int board[MAX_ROWS][MAX_COLUMNS]);

int move_up(int board[MAX_ROWS][MAX_COLUMNS]);

int move_down(int board[MAX_ROWS][MAX_COLUMNS]);

bool can_move_up(int board[MAX_ROWS][MAX_COLUMNS]);

bool can_move_right(int board[MAX_ROWS][MAX_COLUMNS]);

bool can_move_down(int board[MAX_ROWS][MAX_COLUMNS]);

bool can_move_left(int board[MAX_ROWS][MAX_COLUMNS]);

int apply_move_option(int option, int board[MAX_ROWS][MAX_COLUMNS]);

#endif
