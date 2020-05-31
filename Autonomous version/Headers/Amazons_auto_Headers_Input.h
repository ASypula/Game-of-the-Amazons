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


int get_multi_digit_file(FILE* fp, struct game_state* GS);
/**
* Function reads the next sequence of digits from a file
* and combines them into one big number
* @param *fp - file pointer
* @param *GS - game_state
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

int found_horse(game_state* GS, int *dx, int *dy, int x, int y);
/**
* Function checks if a horse is positioned on the board
* @param *GS - game_state
* @param *dx - pointer to x coordinate
* @param *dy - pointer to y coordinate
* @param x - x coordinate from which function is supposed to start checking
* @param y - y coordinate from which function is supposed to start checking
* (x, y) - starting position
* @return 0 - if there is no horse on the board, 1 - if there is a horse
*/

int max_point (game_state* GS, int *dx, int*dy, int x, int y);
/**
* Function finds a tile with maximum number of points (treasure)
* @param *GS - game_state
* @param *dx - pointer to x coordinate
* @param *dy - pointer to y coordinate
* @param x - x coordinate from which function is supposed to start checking
* @param y - y coordinate from which function is supposed to start checking
* (x, y) - starting position
* @return maximum number of found treasure
*/

int tile_available (game_state* GS, int x, int y);
/**
* Function checks if a tile is available for an amazon positioned next to it
* @param *GS - game_state
* @param x - x coordinate of the tile being checked
* @param y - y coordinate of the tile being checked
* @return 0 - if the tile is not available, 1 - if the tile is available
*/

#endif // _Input_H
