#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "common.h"
#include "game.h"

/// LAB 3 - declare LinkedSteps and Sequence data structures

// LinkedStep, contains a GameState pointer named game state and a pointer to the next linked step named next.
typedef struct linked_step{
    GameState *game_state;
    struct linked_step *next;
}LinkedStep;

// Sequence, contains two linked step pointers named first step and last step.
typedef struct{
    LinkedStep *first_step;
    LinkedStep *last_step;
}Sequence;

/// LAB 3 - already implemented functions
void print_linked_steps(LinkedStep *linked_step);

void print_sequence(Sequence *sequence);

/// LAB 3 - implement the following new functions 
LinkedStep* make_linked_step();

void init_linked_step(LinkedStep *linked_step, GameState *game_state);

void free_linked_steps(LinkedStep *linked_step);

Sequence* make_sequence();

void init_sequence(Sequence *sequence);

void free_sequence(Sequence *sequence);

void add_linked_step(Sequence *sequence, GameState *game_state);

#endif 
