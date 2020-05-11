#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "Common.h"
#include "Output.h"
#include "Input.h"
#include "Movement.h"

int main() {

    //Rand seed

    int seed;
    time_t tt;
    seed = time(&tt);
    srand(seed);

    //Declaring structure and first zero values

    game_state state;
    game_state* GS = &state;
    state.point_1.x = 0;
    state.point_1.y = 0;
    state.point_2.x = 0;
    state.point_2.y = 0;
    state.current_player = 0;
    state.n_player = 0;

    //Begining of the Game

    Green_I_txt();
    printf("      .o.                                                                            \n");
    printf("     .888.                                                                           \n");
    printf("    .8'888.     ooo. .oo. .oo.     .oooo.     oooooooo  .ooooo.  ooo..oo.     .oooo.o\n");
    printf("   .8' `888.    `888P'Y88bP'Y88b  `P  )88b   d'''7d8P  d88' `88b `888P'Y88b  d88(  '8\n");
    printf("  .88ooo8888.    888   888   888   .oP'888     .d8P'   888   888  888   888  `'Y88b. \n");
    printf(" .8'     `888.   888   888   888  d8(  888   .d8P'  .P 888   888  888   888  o.  )88b\n");
    printf("o88o     o8888o o888o o888o o888o `Y888''8o d8888888P  `Y8bod8P' o888o o888o 8''888P'\n\n");
    White_txt();
    printf("Please, give the size of the board you want to play on.\n");
    printf("Height: ");
    scanf("%d", &state.fixed.height);
    printf("Width: ");
    scanf("%d", &state.fixed.width);
    system("cls");

    //Allocating memory for the board

    state.board = malloc(state.fixed.height * sizeof(**(state.board)));
    int p = 0;
    while (p < m) {
        *(state.board + p) = malloc(state.fixed.width * sizeof(**state.board));
        p++;
    }

    //Generating board

    generate_board(GS);

    //Geting player info

    get_number_of_players(GS);

    //Allocating memory for a player list

    state.player_list = (int*)malloc(sizeof(int) * state.fixed.number_of_players);

    get_players_names(GS);

    get_number_of_pawns(GS);

    system("cls");

    //Placing amazaons of each player

    place_amazons(GS);

    //Beginning of the movement phase

    //Allocating memory for array of players that are still in game and

    state.still_in_game = (int*)malloc(state.fixed.number_of_players * sizeof(int));

    blank_table(state.still_in_game, state.fixed.number_of_players);

    state.p_with_valid_moves = state.fixed.number_of_players;

    //Main loop of movement phase

    while (state.p_with_valid_moves > 0) {
        if ((state.still_in_game[state.n_player] != FREE) || ending_for_a_player(GS)) {
            if (state.still_in_game[state.n_player] == FREE) {
                state.still_in_game[state.n_player] = OCCUPIED;
                state.p_with_valid_moves--;
            }
        }
        else {
            move_amazon(GS);
        }
        GS->n_player = (GS->n_player + 1) % GS->fixed.number_of_players;
    }

    //Freeing the memory
    while (p < state.fixed.height) {
        free(*(state.board + p));
        p++;
    }
    free(state.board);

    return 0;
}