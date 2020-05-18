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

int main(int argc, char *argv[]) {

    //Rand seed

    int seed;
    time_t tt;
    seed = time(&tt);
    srand(seed);

    //Declaring structure and first zero values

    game_state state;
    game_state* GS = &state;

    state.current_player = 0;
    state.n_player = 0;

    if (argc == 5 && !strcmp(argv[1], "phase=placement")) // four parameters, placement phase
    {
        //Getting player info

        //get_number_of_players(GS);

        //Allocating memory for a player list

        //state.player_list = (int*)malloc(sizeof(int) * state.fixed.number_of_players);

        //get_players_names(GS);

        //Getting the number of amazons
        int i = 8;
        while (argv[2][i++] != "\0")
        {
            state.fixed.number_of_pawns = state.fixed.number_of_pawns * 10 + atoi(argv[2][i]);
        }

        inputfile_name = argv[3];
        outputfile_name = argv[4];
        
        read_file(inputfile_name, GS);

        get_size (GS);

        //Allocating memory for the board
        state.board = malloc(state.fixed.height * sizeof(**(state.board)));
        int p = 0;
        while (p < m) {
            *(state.board + p) = malloc(state.fixed.width * sizeof(**state.board));
            p++;
        }

        //When all amazons are placed on the board, return 1
        if (get_board (GS))
            return 1;

        //Placing amazons of each player

        place_amazons(GS);

        system("cls");
        
        save_data_file(outputfile_name, GS);
    }

    // three parameters, movement phase
    else if (argc == 4 && !strcmp(argv[1], "phase=movement"))
    {
        inputfile_name = argv[2];
        outputfile_name = argv[3];
        
        read_file(inputfile_name, GS);
        
        if (!(get_board (GS)))
            printf ("Not appropriate number of amazons.");
        else
        {
            move_amazon(GS);
        }
        
        save_data_file(outputfile_name, GS);
        
    }

    // one parameter, displaying the name
    else if (argc == 2 && !=strcmp(argv[1], "name"))
    {
        printf ("Name of the player: %s", GS->player_list.name); //needs some changes
    }

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

    //Freeing the memory
    while (p < state.fixed.height) {
        free(*(state.board + p));
        p++;
    }
    free(state.board);

    return 0;
}
