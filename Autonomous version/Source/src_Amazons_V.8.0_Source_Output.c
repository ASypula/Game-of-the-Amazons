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