#ifndef _Input_H
#define _Input_H

#include "Common.h"

int get_number_of_players(game_state* GS);
/**
* gets the number of players and checks if it is less than 9
* @param *GS - game_state
*/

void get_players_names(game_state* GS);
/**
* gets players names
* ascribes ID and initial number of points=0 to each player in structure player_data player
* @param *GS - game_state
*/

void place_amazons(game_state* GS);
/**
* place amazons on the board
* deletes artifacts and points from chosen tiles
* changes occupation for player ID number in structure tile board
* @param *GS - game_state
*/

void get_size(game_state* GS);
/**
* gets size of the board,
* saves the number of rows in GS->fixed_inf.height
* saves the number of columns in GS->fixed_inf.width
* @param *GS - game_state
*/

tile get_tile(game_state* GS);
/**
* saves three pieces of information (digits) about tile: treasure, artifact and occupation
* @param *GS - game_state
* @return tile
*/

void get_board(game_state* GS);
/**
* gets information about whole board (all tiles)
* saves the positions of ones amazon
* @param *GS - game_state
* @return 1 if all the pawns are placed on the board, 0 otherwise
*/

void choose_tile(game_state* GS, int* x, int* y);
/**
* Function reads the hitten key (Or combination) and changes the coordiantes form the definition:
* Up - moves 1 tile up (y-1)
* Ctrl + UP - moves 5 tiles up (y-5)
* Down - moves 1 tile down (y+1)
* Ctrl + Down - moves 5 tiles down (y+5)
* Left - moves 1 tile left (x-1)
* Ctrl + Left - moves 5 tiles left (x-5)
* Right - moves 1 tile rigt (x+1)
* Ctrl + Right - moves 5 tiles right (x+5)
* @param *GS - game_state
* @param *x - x coordinate
* @param *y - y coordinate
*/

void get_move_with_arrowkey(game_state* GS, int* x, int* y);
/**
* Function creates menu with instrunctions for the user how to choose a tile by using arrowkeys
* and ends with press of enter
* @param *x - x coordinate
* @param*y - y coordinate
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

void read_file(char* file_name, struct game_state* GS)''
/**
* Function reads specific data from file and saves it in the data base
* (allocates memory needed for data)
* @param *file_name - name of a file
* @param *GS - game_state
*/

#endif // _Input_H
