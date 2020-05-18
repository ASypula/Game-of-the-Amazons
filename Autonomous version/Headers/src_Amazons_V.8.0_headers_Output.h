#ifndef _Output_H
#define _Output_H

#include "Common.h"

void generate_board(struct game_state* GS);
/**
* A function fills each tile of the board with random treasure and artifact
* @param *GS - game_state
*/


//Function drawing given board with colors
void draw_board_color(struct game_state* GS);
/**
* A function draws a board using colors
* @param *GS - game_state
*/

void order_scores(struct game_state* GS);
/*
* Creates a new structure by copying the player structure
* sorts a new structure by the number of points
* @param *GS - game state
*/

void add_player_data_file(FILE* fp, struct game_state* GS);
/*
* Saves in file data about player_data
* @param *fp - file pointer
* @param *GS - game_state
*/

void add_size_file(FILE* fp, struct game_state* GS);
/*
* Saves in file data about size
* @param *fp - file pointer
* @param *GS - game_state
*/

void add_tiles_file(FILE* fp, struct game_state* GS);
/*
* Saves in file data about files
* @param *fp - file pointer
* @param *GS - game_state
*/

void save_data_file(char* file_name, struct game_state* GS);
/*
* Saves in file stored data from a game_state
* @param *file_name - name of the file
* @param *GS - game_state
*/

#endif // _Output_H