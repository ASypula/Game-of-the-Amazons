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
        
        int i = 8;
        while (argv[2][i++] != "\0")
        {
            state.fixed.number_of_pawns = state.fixed.number_of_pawns * 10 + atoi(argv[2][i]);
        }
        
        read_file(argv[3], GS);

        //Placing amazons

        place_amazons(GS);

        system("cls");
        
        save_data_file(argv[4], GS);
    }

    // three parameters, movement phase
    else if (argc == 4 && !strcmp(argv[1], "phase=movement"))
    {
        //inputfile_name = argv[2];
        //outputfile_name = argv[3];
        
        read_file(argv[2], GS);
        
        if (GS->already_placed_amazons < GS->fixed.number_of_pawns)
            printf ("Not appropriate number of amazons.");
        else
        {
            move_amazon(GS);
        }
        
        save_data_file(argv[3], GS);
        
    }

    // one parameter, displaying the name
    else if (argc == 2 && !=strcmp(argv[1], "name"))
    {
        printf ("Name of the player: %s", GS->player_list.name); //needs some changes
    }

    //Beginning of the Game

    Green_I_txt();
    printf("      .o.                                                                            \n");
    printf("     .888.                                                                           \n");
    printf("    .8'888.     ooo. .oo. .oo.     .oooo.     oooooooo  .ooooo.  ooo..oo.     .oooo.o\n");
    printf("   .8' `888.    `888P'Y88bP'Y88b  `P  )88b   d'''7d8P  d88' `88b `888P'Y88b  d88(  '8\n");
    printf("  .88ooo8888.    888   888   888   .oP'888     .d8P'   888   888  888   888  `'Y88b. \n");
    printf(" .8'     `888.   888   888   888  d8(  888   .d8P'  .P 888   888  888   888  o.  )88b\n");
    printf("o88o     o8888o o888o o888o o888o `Y888''8o d8888888P  `Y8bod8P' o888o o888o 8''888P'\n\n");
    White_txt();


    //Freeing the memory
    while (p < state.fixed.height) {
        free(*(state.board + p));
        p++;
    }
    free(state.board);
    free(GS->player_list);
    free(GS->positions);
    free(GS);

    return 0;
}
