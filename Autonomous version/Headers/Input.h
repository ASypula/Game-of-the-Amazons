#ifndef _Input_H
#define _Input_H

#include "Common.h"
#include <stdio.h>


int place_amazons(game_state* GS);
/**
* places one amazon on the board
* deletes artifacts and points from chosen tiles
* changes occupation for player ID number in structure tile board
* @param *GS - game_state
* @return 1 if amazon was placed, 0 if amazon cannot be placed on the board
*/


int get_multi_digit_file(FILE* fp, struct game_state* GS);
/**
* Function reads the next sequence of digits from a file
* and combines them into one big number
* @param *fp - file pointer
* @param *GS - game_state
* @return int - number 
*/

tile get_tile_file(FILE* fp, struct game_state* GS, int i, int j);
/**
* Function reads next 3 digits from the file (tile) and returns them as
* a tile structure
* @param *fp - file pointer
* @param *GS - game_state
* @param i - x coordinate of readead tile
* @param j - y coordinate of readead tile
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

int max_point (game_state* GS, int *dx, int*dy, int x, int y, int search_max);
/**
* Function finds a tile with maximum number of points (treasure)
* @param *GS - game_state
* @param *dx - pointer to x coordinate
* @param *dy - pointer to y coordinate
* @param x - x coordinate from which function is supposed to start checking
* @param y - y coordinate from which function is supposed to start checking
* (x, y) - starting position
* @param search_max - maximum value of treasure that may still be available for an amazon (that is yet to be checked) 
* @return 1 if a tile with search_max treasure was found, 0 if it wasn't
*/

int tile_available (game_state* GS, int x, int y, int *found_x, int *found_y);
/**
* Function checks if a tile is available for an amazon positioned next to it
* @param *GS - game_state
* @param x - x coordinate of the tile being checked
* @param y - y coordinate of the tile being checked
* @param *found_x - pointer to x coordinate
* @param *found_y - pointer to y coordinate
* (*found_x, *found_y) - a tile chosen to move the amazon
* @return 0 - if the tile is not available, 1 - if the tile is available
*/

int best_place (game_state* GS, int *found_x, int *found_y);
/**
* Function searches for the best tile to move the amazon
* first looks for a tile close to a horse
* second looks for a tile with the highest treasure
* @param *GS - game_state
* @param *found_x - pointer to x coordinate
* @param *found_y - pointer to y coordinate
* (*found_x, *found_y) - a tile chosen to move the amazon
* @return 1 - if a tile to move an amazon was found, 0 - if no amazon can be placed on the board
*/

#endif // _Input_H
