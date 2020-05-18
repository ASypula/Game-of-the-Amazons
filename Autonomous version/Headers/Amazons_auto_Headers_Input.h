#ifndef _Input_H
#define _Input_H

#include "Common.h"


void place_amazons(game_state* GS);
/**
* place amazons on the board
* deletes artifacts and points from chosen tiles
* changes occupation for player ID number in structure tile board
* @param *GS - game_state
*/


int get_multi_digit_file(FILE* fp);
/**
* Function reads the next sequence of digits from a file
* and combines them into one big number
* @param *fp - file pointer
* @return int - number 
*/

tile get_tile_file(FILE* fp, struct game_state* GS);
/**
* Function reads next 3 digits from the file (tile) and returns them as
* a tile structure
* @param *fp - file pointer
* @param *GS - game_state
* @return tile - data of a tile
*/

void get_board_file(FILE* fp, struct game_state* GS);
/**
* Function reads every tile from a file and saves it in the data base
* @param *fp - file pointer
* @param *GS - game_state
*/

void get_player_data_file(FILE* fp, struct game_state* GS);
/**
* Function reads player_data from a file and saves it in the data base
* @param *fp - file pointer
* @param *GS - game_state
*/

void read_file(char* file_name, struct game_state* GS);
/**
* Function reads specific data from file and saves it in the data base
* (allocates memory needed for data)
* @param *file_name - name of a file
* @param *GS - game_state
*/

#endif // _Input_H
