#include "main.h"

void run_game(Session *session){
    GameState *game_state = session->current_game_state;
    Sequence *sequence = session->current_sequence;

    bool finish_game = is_terminal(game_state->board); 

    while(!finish_game){
        // 1. Print data
        printf("Best score: %d\n", session->best_score);
        print_game_state(game_state);

        // 2. Select a move
        int game_option; 
        do{
            print_options(game_state->board);
            printf("Enter a game option: ");
            game_option = read_int(); // ToDo: modify it with arrows
        }while(!is_valid_option(game_option, game_state->board));
        
        // 3.a Quit game
        if(game_option == QUIT_GAME)
            return;
        // 3.b Show best move
        if(game_option == SHOW_BEST_MOVE){
            show_best_move(game_state);
            continue;
        }

        // 3.c Apply the move
        int score = apply_move_option(game_option, game_state->board);

        // 4. Update scores
        game_state->score += score;
        session->best_score = max(session->best_score, game_state->score);
        
        // 5. Add new number
        finish_game = is_terminal(game_state->board);
        if(!finish_game){
            add_random_number(game_state->board);
            finish_game = is_terminal(game_state->board);
        }

        add_linked_step(sequence, game_state);

    };

    if(is_goal(game_state->board)) 
        printf("You won!!!\n");
    else printf("You lost :-(\n");
    
    print_game_state(game_state);
}

void new_game(Session *session){
    // @brief Restarts session GameState and Sequence,
    //        adds the current GameState to the sequence
    //        and runs a new game
    // @Returns: nothing
    
    /**********************************************/
    /******** LAB 3 - implement next steps ********/
    /**********************************************/
    // 1. restarts session GameState and Sequence
    
    // 2. Adds the current game state to the current
    //    sequence in the session

    // 3. Runs game
    restart_session_game_state(session);
    restart_session_sequence(session);
    run_game(session);
}

void save_game(Session *session){
    // @brief Writes session sequence to a FILE
    // @Returns: nothing

    // 1. Checks for Sequence errors
    Sequence *seq = session->current_sequence;
    if(seq == NULL){
        printf("Error, session sequence is NULL\n");
        return;
    }
    if(seq->first_step == NULL){
        printf("Error, session sequence is empty\n");
        return;
    }

    // 2. Set filename variable from standard input
    printf("Enter a filename: ");
    char filename[MAX_STR_LENGTH];
    read_filename(filename);

    /**********************************************/
    /******** LAB 3 - implement next steps ********/
    /**********************************************/
    // 3. Opens the filename FILE in writing-mode and
    //    checks that no errors are produced
    FILE *file_w = fopen(filename,"w");

    // 4. Prints data to opened file as follows:
    //     - print the score of the first step and jump 
    //       to the next line,
    //     - for each row in the board matrix, print all
    //       numbers for that row separated by blank spaces
    //       and jump to next line for each new row
    //     - move to the next step in the sequence
    //    
    fprintf(file_w,"%d\n",session->current_game_state->score);
    for(int i = 0;i<MAX_ROWS;i++){
        for(int j = 0;j<MAX_COLUMNS;j++){
        fprintf(file_w,"%d ",session->current_game_state->board[i][j]);
        }
        fprintf(file_w,"\n");
    }
    // 5. Closes the file
    fclose(file_w);
}

void load_game(Session *session){
    // @brief Reads a session sequence from a FILE
    // @Returns: nothing

    // 1. Sets filename variable from standard input
    printf("Enter a filename: ");
    char filename[MAX_STR_LENGTH];
    read_filename(filename);
    
    /**********************************************/
    /******** LAB 3 - implement next steps ********/
    /**********************************************/
    // 2. Opens the filename FILE in reading-mode and
    //    checks that no errors are produced
    FILE *file_r = fopen(filename,"r");
    if (file_r == NULL){
        // If "filename" does not exist, then print the information
        // And pass this part
        printf("\nDocument not found!\n");
    }
    else{
    // 3. Restarts session sequence and game state
    restart_session_game_state(session);
    restart_session_sequence(session);
    
    // 4. Reads data from file with the same structure
    //    as it was saved, then adds the game state to
    //    the sequence
    fscanf(file_r,"%d ",&session->current_game_state->score);

    for(int i = 0;i<MAX_ROWS;i++){
        for(int j = 0;j<MAX_COLUMNS;j++){
            fscanf(file_r,"%d ",&session->current_game_state->board[i][j]);
        }
    }
    run_game(session);
    }
    // 5. Closes file
    fclose(file_r);
}

void resume_game(Session *session){
    // @brief Resumes the current game state of the session
    // @Returns: nothing
        
    /**********************************************/
    /******** LAB 3 - implement next steps ********/
    /**********************************************/    
    
    // 1. Checks the current game state of the session
    //    is not NULL, otherwise returns
    
    // 2. Checks the current sequence of the session is
    //    not NULL, otherwise returns
    
    // 3. Runs a game
    if (session != NULL){
        if (session->current_sequence != NULL){
            run_game(session);
        }
        else{
            printf("Error resuming game\n");
            return;
        }
    }
    else{
        printf("Error resuming game\n");
        return;
    }
}

void print_menu(){
    printf("Menu options:\n");
    printf("\t1. New game.\n");
    printf("\t2. Save game.\n"); 
    printf("\t3. Load game.\n"); 
    printf("\t4. Resume game.\n"); 
    printf("\t5. Exit.\n");  
}


void run(Session *session){
    int option;
    do{
        print_menu();
        do{
            printf("Enter an integer (%d-%d): ", NEW_GAME, EXIT);
            option = read_int();
        }while(option < NEW_GAME || option > EXIT);

        switch (option){
        case NEW_GAME:
            new_game(session);
            break;
        case SAVE_GAME:
            save_game(session);
            break;
        case LOAD_GAME:
            load_game(session);
            break;
        case RESUME_GAME:
            resume_game(session);
            break;
        case EXIT:
            break;
        }
    }while(option != EXIT);
}

int main(){
    // LAB 2 - create a session variable and pass its reference
	//         to initialize the session and run the application

    // Declares Session variables and passes adresses to init_session and run function
    Session session;
    init_session(&session);
    run(&session);
    // LAB 3 - free the session data
    free_session(&session);
}
