#ifndef _Input_H
#define _Input_H

#include "Common.h"

int get_number_of_players(game_state* GS);
/*gets the number of players and checks if it is less than 9
	*GS - game_state*/

void get_players_names(game_state* GS);
/* gets players names
   ascribes ID and initial number of points=0 to each player in structure player_data player 
	*GS - game_state */

void get_number_of_pawns(game_state* GS);
/* gets number of pawns each player has
	*GS - game_state */

void place_amazons(game_state* GS);
/* place amazons on the board
   deletes artefacts and points from chosen tiles
   changes occupation for player ID number in structure tile board
	*GS - game_state */

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
*/

void get_board(game_state* GS);
/** 
* gets information about whole board (all tiles)
* @param *GS - game_state
*/

void choose_tile(game_state* GS, int* x, int* y);
/*
	Function reads the hitten key (Or combination) and changes the coordiantes form the definition:
	Up - moves 1 tile up (y-1)
	Ctrl + UP - moves 5 tiles up (y-5)
	Down - moves 1 tile down (y+1)
	Ctrl + Down - moves 5 tiles down (y+5)
	Left - moves 1 tile left (x-1)
	Ctrl + Left - moves 5 tiles left (x-5)
	Right - moves 1 tile rigt (x+1)
	Ctrl + Right - moves 5 tiles right (x+5)
	*GS - game_state
	*x - x coordinate
	*y - y coordinate
*/

void get_move_with_arrowkey(game_state* GS, int* x, int* y);
/*
	Function creates menu with instractions for the user how to choose a tile by using arrowkeys
	and ends with press of enter
	*x - x coordinate
	*y - y coordinate
*/

#endif // _Input_H
