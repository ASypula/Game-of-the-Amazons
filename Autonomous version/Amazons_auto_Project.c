#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Common.h"
#include "Output.h"
#include "Input.h"
#include "Movement.h"

int main(int argc, char *argv[]) {

    //Declaring structure and first zero values

    game_state state;
    game_state* GS = &state;
    GS->name = (char*) malloc (NAME_LENGTH * sizeof(char));
    GS->name = "DoubleA";

    state.error = 0;
    state.current_player = 0;
    state.n_player = 0;
    state.fixed.number_of_pawns = 0;

    if (argc == 5 && !strcmp(argv[1], "phase=placement")) // four parameters, placement phase
    {
        int i = 0;
        char c;
        if (argv[2][i++] == 'a' && argv[2][i++] == 'm' && argv[2][i++] == 'a' && argv[2][i++] == 'z' && argv[2][i++] == 'o' && argv[2][i++] == 'n' && argv[2][i++] == 's' && argv[2][i++] == '=')
        {
            while ((c = argv[2][i++]) != '\0')
            {
                if (!is_digit(c))
                {
                    printf ("Number of amazons is supposed to be a number\n");
                    break;
                }
                else
                    state.fixed.number_of_pawns = state.fixed.number_of_pawns * 10 + (c - '0');
            }
        }

        read_file(argv[3], GS);
        if (state.error == 1) {
            return 2;
        }
        else{
            //Placing amazons
            if(place_amazons(GS))
            {
                save_data_file(argv[4], GS);
                free_memory(GS);
                return 0;
            }
            else
            {
                printf ("Amazon cannot be placed on the board\n");
                return 1;
            }
        }
    }

    // three parameters, movement phase
    else if (argc == 4 && !strcmp(argv[1], "phase=movement"))
    {
        //inputfile_name = argv[2];
        //outputfile_name = argv[3];

        read_file(argv[2], GS);

        if (state.error == 1) {
            return 2;
        }
        else {
            if (move_amazon(GS))
            {
                save_data_file(argv[3], GS);
                free_memory(GS);
                return 0;
            }
            else
            {
                printf("All amazons are blocked\n");
                free_memory(GS);
                return 1;
            }
        }
    }

    // one parameter, displaying the name
    else if (argc == 2 && !strcmp(argv[1], "name"))
    {
        printf ("Name of the player: %s", GS->name);
        free_memory(GS);
    }

    else
    {
        printf ("Not defined command line parameters\n");   //czy 3 jako return?
        return 3;
    }

}
