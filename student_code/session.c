#include "session.h"

/********************************************************/
/************* LAB 3 - functions to refactor ************/
/********************************************************/
void init_session(Session *session){
    // @brief Sets the best score of the session to 0 and
    //        the session game state and sequence to NULL
    // @Returns: nothing
    session->best_score = 0;
    session->current_game_state = NULL;
    session->current_sequence = NULL;
}

void restart_session_game_state(Session *session){
    // @brief Frees the current game state in the session 
    //        if it is not NULL, makes a new game state 
    //        and initializes it
    // @Returns: nothing
    if (session->current_game_state != NULL){
        free(session->current_game_state);
    }
    session->current_game_state = make_game_state();
    init_game_state(session->current_game_state);
}

/********************************************************/
/************* LAB 3 - functions to program *************/
/********************************************************/
void restart_session_sequence(Session *session){
    // @brief Frees the current sequence in the session if 
    //        it is not NULL, makes a new game state and 
    //        initializes it
    // @Returns: nothing
    if (session->current_sequence != NULL){
        free(session->current_sequence);
    }
    session->current_sequence = make_sequence();
    init_sequence(session->current_sequence);
}


void free_session(Session *session){
    // @brief Frees the current game state and sequence 
    //        in the session if they are not NULL
    // @Returns: nothing
    /*
    if (session->current_game_state != NULL && session->current_sequence != NULL){
        free(session->current_game_state);
        free(session->current_sequence);
    }
    */
    free_sequence(session->current_sequence);
    free_game_state(session->current_game_state);
}
