#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Common.h"
#include "Output.h"
#include "Input.h"
#include "Movement.h"

int main(int argc, char* argv[]) {

#ifdef RUN_UNIT_TEST

    //Testing of reading file - TEST.txt

    game_state u_test;
    game_state* UT = &u_test;
    UT->name = (char*)malloc(NAME_LENGTH * sizeof(char));
    UT->name = "DoubleA";

    u_test.error = 0;
    u_test.current_player = 0;
    u_test.n_player = 0;
    u_test.fixed.number_of_pawns = 0;

    read_file("TEST.txt", UT);

    test(TRUE, UT->fixed.height == 5, "Read_height");
    test(TRUE, UT->fixed.width == 6, "Read_width");
    test(TRUE, UT->board[4][0].occupation == 5, "Read_occupation");
    test(TRUE, UT->board[2][5].treasure == 3, "Read_treasure");
    test(TRUE, UT->board[0][2].artifact == 2, "Read_artifact");
    test(TRUE, UT->fixed.number_of_players == 5, "Read_number_of_players");
    test(TRUE, !strcmp("DoubleA", UT->player_list[0].name), "Read_name");
    test(TRUE, UT->player_list[4].ID == 5, "Read_ID");
    test(TRUE, UT->player_list[1].points == 38, "Read_points");
    test(TRUE, find_ID(UT) == 1, "Find_our_ID");
    test(TRUE, fmax_of8(-12, 0, 3, 4, 5, 87, 256, 19) == 256, "Find_max_of_eight");
    test(FALSE, is_occupied(UT, 2, 2), "Check_if_occupied");

#endif // RUN_UNIT_TEST

    //Game state
    game_state state;
    game_state* GS = &state;
    GS->name = (char*)malloc(NAME_LENGTH * sizeof(char));
    GS->name = "DoubleA";

    state.error = 0;
    state.current_player = 0;
    state.n_player = 0;
    state.fixed.number_of_pawns = 0;

    //Ac system
    game_state check;
    game_state* TEST = &check;
    TEST->name = (char*)malloc(NAME_LENGTH * sizeof(char));
    TEST->name = "DoubleA";

    check.error = 0;
    check.current_player = 0;
    check.n_player = 0;
    check.fixed.number_of_pawns = 0;

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
                    printf("Number of amazons is supposed to be a number\n");
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
        else {
            //Placing amazons
            if (place_amazons(GS))
            {
                save_data_file(argv[4], GS);
                return 0;
            }
            else
            {
                printf("Amazon cannot be placed on the board\n");
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
        read_file("AC.txt", TEST);

        if (state.error == 1) {
            return 2;
        }
        else {

            //AC SYSTEM
            if (!TEST->error) {
                ac_system(GS, TEST);
            }

            if (move_amazon(GS))
            {

                save_data_file(argv[3], GS);
                save_data_file("AC.txt", GS);
                return 0;
            }
            else
            {
                printf("All amazons are blocked\n");
                return 1;
            }
        }
    }

    // one parameter, displaying the name
    else if (argc == 2 && !strcmp(argv[1], "name"))
    {
        printf("%s", GS->name);
    }

    else
    {
        printf("Not defined command line parameters\n");
        return 2;
    }
}