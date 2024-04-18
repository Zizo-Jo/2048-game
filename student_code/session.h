#ifndef _SESSION_H_
#define _SESSION_H_ 

#include "game.h"
#include "sequence.h"


/// LAB 3 - refactor Session declaration, which should contain:
///          - a best_score integer,
///          - a GameState pointer named current_game_state,
///          - a Sequence pointer named current_sequence.
typedef struct{
    int best_score;
    GameState *current_game_state;
    Sequence *current_sequence;
}Session;

/// LAB 3 - refactor following functions for pointer management
void restart_session_game_state(Session *session);

void init_session(Session *session);

/// LAB 3 - implement the following new functions
void free_session(Session *session);

void restart_session_sequence(Session *session);

#endif
