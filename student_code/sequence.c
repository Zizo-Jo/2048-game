#include "sequence.h"

/********************************************************/
/********* LAB 3 - functions already implemented ********/
/********************************************************/

void print_linked_steps(LinkedStep *linked_step){
    // @brief Prints the game state of every linked step
    // @Returns: nothing
    int n_step = 1;
    LinkedStep *aux = linked_step;
    while(aux != NULL){
        printf("Step #%d\n", n_step);
        print_game_state(aux->game_state);
        aux = aux->next;
        ++n_step;
    }
}

void print_sequence(Sequence *sequence){
    // @brief Either prints no data if the sequence or first_step are
    //        NULL, or prints all linked steps from the first step
    // @Returns: nothing
    printf("Game states sequence:\n");
    if(sequence == NULL || sequence->first_step == NULL){
        printf("No data!!!\n");
    }
    else{
        print_linked_steps(sequence->first_step);
    }
}

/********************************************************/
/************* LAB 3 - functions to program *************/
/********************************************************/

LinkedStep* make_linked_step(){
    // @brief Allocates memory for a LinkedStep and
    //        returns its address
    // @Returns: a pointer to a new LinkedStep variable
    LinkedStep *new_linked_step = malloc(sizeof(*new_linked_step));
    return new_linked_step;
}

void init_linked_step(LinkedStep *linked_step, GameState *game_state){
    // @brief Initializes linked_step, where its game state is a copy
    //        of the game_state in the function argument and the next
    //        step is NULL
    // @Returns: nothing
    linked_step->game_state = game_state;
    linked_step->next = NULL;
}

void free_linked_steps(LinkedStep *linked_step){
    // @brief Frees all allocated memory in linked_step
    // @Returns: nothing
    if (linked_step != NULL){
        free(linked_step);
    }
}

Sequence* make_sequence(){
    // @brief Allocates memory for a Sequence and returns its address
    // @Returns: a pointer to a new Sequence variable
    Sequence *new_sequence = malloc(sizeof(*new_sequence));
    return new_sequence;
}

void init_sequence(Sequence *sequence){
    // @brief Initializes sequence with first and last steps as NULL
    // @Returns: nothing
    sequence->first_step = NULL;
    sequence->last_step = NULL;
}

void free_sequence(Sequence *sequence){
    // @brief Frees the allocated memory for a Sequence
    // @Returns: nothing
    if (sequence != NULL){
        free(sequence);
    }
}

void add_linked_step(Sequence *sequence, GameState *game_state){
    // @brief Makes a new linked step, initializes it with game_state,
    //        then checks if it is the first step, or must be appended
    //        as the last step
    // @Returns: nothing
    LinkedStep *new_linked_step = make_linked_step();
    init_linked_step(new_linked_step, game_state);
    if (sequence->first_step == NULL){
        sequence->first_step = new_linked_step;
        sequence->last_step = new_linked_step;
    }
    else{
        sequence->last_step->next = new_linked_step;
        sequence->last_step = new_linked_step;
    }
}