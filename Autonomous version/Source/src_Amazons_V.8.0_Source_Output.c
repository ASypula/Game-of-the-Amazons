#include "Output.h"

void add_player_data_file(FILE* fp, struct game_state* GS) {
    int i;

    for (i = 0; i < GS->fixed.number_of_players; i++) {
        fprintf(fp, "%s ", GS->player_list[i].name);
        fprintf(fp, "%d ", GS->player_list[i].ID);
        fprintf(fp, "%d\n", GS->player_list[i].points);


    }
}

void add_size_file(FILE* fp, struct game_state* GS) {
    fprintf(fp, "%d %d\n", GS->fixed.height, GS->fixed.width);
}

void add_tiles_file(FILE* fp, struct game_state* GS) {
    int i, j;

    for (i = 0; i < GS->fixed.height; i++) {
        for (j = 0; j < GS->fixed.width; j++) {
            if (j == (GS->fixed.width - 1)) {
                fprintf(fp, "%d%d%d\n", GS->board[i][j].treasure, GS->board[i][j].artifact, GS->board[i][j].occupation);
            }
            else {
                fprintf(fp, "%d%d%d ", GS->board[i][j].treasure, GS->board[i][j].artifact, GS->board[i][j].occupation);
            }
        }
    }
}

void save_data_file(char* file_name, struct game_state* GS) {

    FILE* fp = fopen(file_name, "w");

    if (fp == NULL) {
        printf("Error in saving file!");
    }
    else {
        //Printing size

        add_size_file(fp, GS);

        //Printing tiles

        add_tiles_file(fp, GS);

        //Printing player data

        add_player_data_file(fp, GS);

        fclose(fp);
    }
}

int ac_used_horses(struct game_state* GS, struct game_state* TEST) {

    int count_horse_AC = 0, count_horse_now = 0;

    int i, j;

    for (i = 0; i < GS->fixed.height; i++) {
        for (j = 0; j < GS->fixed.width; j++) {
            if (GS->board[i][j].artifact == HORSE) {
                count_horse_now++;
            }
        }
    }

    for (i = 0; i < TEST->fixed.height; i++) {
        for (j = 0; j < TEST->fixed.width; j++) {
            if (TEST->board[i][j].artifact == HORSE) {
                count_horse_AC++;
            }
        }
    }

    return count_horse_AC - count_horse_now;
}

int ac_used_broken_arrows(struct game_state* GS, struct game_state* TEST) {

    int count_broken_arrow_AC = 0, count_broken_arrow_now = 0;

    int i, j;

    for (i = 0; i < GS->fixed.height; i++) {
        for (j = 0; j < GS->fixed.width; j++) {
            if (GS->board[i][j].artifact == BROKEN_ARROW) {
                count_broken_arrow_now++;
            }
        }
    }

    for (i = 0; i < TEST->fixed.height; i++) {
        for (j = 0; j < TEST->fixed.width; j++) {
            if (TEST->board[i][j].artifact == BROKEN_ARROW) {
                count_broken_arrow_AC++;
            }
        }
    }

    return count_broken_arrow_AC - count_broken_arrow_now;
}

void ac_points_check(struct game_state* GS, struct game_state* TEST, int used_horse) {

    int max_points_turn = 5 + used_horse * 5;
    int difference;
    int i;

    for (i = 0; i < GS->fixed.number_of_players; i++) {
        difference = TEST->player_list[i].points - GS->player_list[i].points;

        if (difference < 0) {
            printf("Player %s lost points this turn!", GS->player_list[i].name);
        }
        else if (difference > max_points_turn) {
            printf("Players %s achieved this turn more points than it is possible!", GS->player_list[i].name);
        }
    }

}

void ac_arrow_check(struct game_state* GS, struct game_state* TEST, int used_horse, int used_broken_arrow) {

    int count_arrows_now = 0, count_arrows_AC = 0;
    int shoot_arrows = 0;
    int i, j;

    for (i = 0; i < GS->fixed.height; i++) {
        for (j = 0; j < GS->fixed.width; j++) {
            if (GS->board[i][j].occupation == MISSILE) {
                count_arrows_now++;
            }
        }
    }

    for (i = 0; i < TEST->fixed.height; i++) {
        for (j = 0; j < TEST->fixed.width; j++) {
            if (TEST->board[i][j].occupation == MISSILE) {
                count_arrows_AC++;
            }
        }
    }

    shoot_arrows = count_arrows_now - count_arrows_AC;

    int possible_shots = GS->fixed.number_of_players + used_horse - used_broken_arrow;

    if (shoot_arrows != possible_shots) {
        printf("Warning! In the last turn, players shoot %d missiles when it should be %d missiles", shoot_arrows, possible_shots);
    }
}

int ac_pawn_positions(struct game_state* GS, struct game_state* TEST, struct coordinate* position_now, struct coordinate* position_AC, int i) {

    int count = 0;
    int j, k;

    //Sprawdzanie lokalizacji poprzednich pionów
    for (j = 0; j < TEST->fixed.height; j++) {
        for (k = 0; k < TEST->fixed.width; k++) {
            if ((i + 1) == TEST->board[k][j].occupation) {
                position_AC[count].x = k;
                position_AC[count++].y = j;
            }
        }
    }
    count = 0;

    //Sprawdzanie lokalizacji obecnych pionów
    for (j = 0; j < GS->fixed.height; j++) {
        for (k = 0; k < GS->fixed.width; k++) {
            if ((i + 1) == GS->board[k][j].occupation) {
                position_now[count].x = k;
                position_now[count++].y = j;
            }
        }
    }

    return count;
}

int ac_horizontal_move(struct game_state* GS, struct coordinate* position_now, struct coordinate* position_AC, int j) {

    int possible = 0;
    int k;

    //UP
    for (k = position_AC[j].x; k > 0; k--) {
        if (k == position_now[j].x && position_AC[j].y == position_now[j].y) {
            possible = 1;
        }
    }

    //Down
    for (k = position_AC[j].x; k < GS->fixed.height; k++) {
        if (k == position_now[j].x && position_AC[j].y == position_now[j].y) {
            possible = 1;
        }
    }

    return possible;
}

int ac_vertical_move(struct game_state* GS, struct coordinate* position_now, struct coordinate* position_AC, int j) {

    int possible = 0;
    int k;

    //Left
    for (k = position_AC[j].y; k > 0; k--) {
        if (position_AC[j].x == position_now[j].x && k == position_now[j].y) {
            possible = 1;
        }
    }

    //Right
    for (k = position_AC[j].y; k < GS->fixed.height; k++) {
        if (position_AC[j].x == position_now[j].x && k == position_now[j].y) {
            possible = 1;
        }
    }

    return possible;
}

int ac_diagonal_move(struct game_state* GS, struct coordinate* position_now, struct coordinate* position_AC, int j) {

    int possible = 0;
    int k, l;

    //Up-Right

    k = position_AC[j].x;
    l = position_AC[j].y;
    while ((k > 0) || (l < GS->fixed.width)) {
        if (k == position_now[j].x && l == position_now[j].y) {
            possible = 1;
        }

        k--;
        l++;
    }

    //Up-Left

    k = position_AC[j].x;
    l = position_AC[j].y;
    while ((k > 0) || (l > 0)) {
        if (k == position_now[j].x && l == position_now[j].y) {
            possible = 1;
        }

        k--;
        l--;
    }

    //Down-Right

    k = position_AC[j].x;
    l = position_AC[j].y;
    while ((k < GS->fixed.height) || (l < GS->fixed.width)) {
        if (k == position_now[j].x && l == position_now[j].y) {
            possible = 1;
        }

        k++;
        l++;
    }

    //Down-Left

    k = position_AC[j].x;
    l = position_AC[j].y;
    while ((k < GS->fixed.height) || (l > 0)) {
        if (k == position_now[j].x && l == position_now[j].y) {
            possible = 1;
        }

        k++;
        l--;
    }

    return possible;

}

void ac_check_move(struct game_state* GS, struct game_state* TEST, struct coordinate* position_now, struct coordinate* position_AC, int i, int count){

            int possible = 0;

            int j, k, l;

            for(j=0; j<count; j++){
                if(!cmp_coordinates(position_AC[j], position_now[j])){

                    //Horizontally

                    if(ac_horizontal_move(GS, position_now, position_AC, j)){
                        possible = 1;
                    }

                    //Vertically

                    if(ac_vertical_move(GS, position_now, position_AC, j)){
                        possible = 1;
                    }

                    //Diagonally

                    if(ac_diagonal_move(GS, position_now, position_AC, j)){
                        possible = 1;
                    }

                    if(!possible){
                        printf("Player %s made impossible move with his amazon!\n", GS->player_list[i].name);
                    }
                }
            }
            count = 0;
        }

void ac_system(struct game_state* GS, struct game_state* TEST) {

    //Horse difference

    int used_horse = ac_used_horses(GS, TEST);

    //Broken arrow difference

    int used_broken_arrow = ac_used_broken_arrows(GS, TEST);

    //Sprawdzanie ruchu (jeśli nie były użyte konie)

    int i, j, k;

    if (!used_horse) {

        for (i = 0; i < GS->fixed.number_of_players; i++) {

            //pawn positions (Arrays)
            coordinate* position_now;
            position_now = (coordinate*)malloc(sizeof(coordinate) * GS->fixed.number_of_pawns);
            coordinate* position_AC;
            position_AC = (coordinate*)malloc(sizeof(coordinate) * GS->fixed.number_of_pawns);

            int count = ac_pawn_positions(GS, TEST, position_now, position_AC, i);

            ac_check_move(GS, TEST, position_now, position_AC, i, count);
        }
    }

    //Points check

    ac_points_check(GS, TEST, used_horse);


    //Arrow check

    ac_arrow_check(GS, TEST, used_horse, used_broken_arrow);
}
