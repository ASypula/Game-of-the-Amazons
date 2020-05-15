#ifndef _Output_H
#define _Output_H

#include "Common.h"

void White_txt();
/**
* Function changes color of displayed symbols to:
* White
*/

void White_bold_txt();
/**
* Function changes color of displayed symbols to:
* Bolded white
*/

void Yellow_I_txt();
/**
* Function changes color of displayed symbols to:
* Intense yellow
*/

void Green_txt();
/**
* Function changes color of displayed symbols to:
* Green
*/

void Green_I_txt();
/**
* Function changes color of displayed symbols to:
* Bolded Green
*/

void Blue_txt();
/**
* Function changes color of displayed symbols to:
* Blue
*/

void Blue_I_txt();
/**
* Function changes color of displayed symbols to:
* Bolded Blue
*/

void Magenta_txt();
/**
* Function changes color of displayed symbols to:
* Magenta
*/

void Magenta_I_txt();
/**
* Function changes color of displayed symbols to:
* Bolded Magenta
*/

void Red_txt();
/**
* Function changes color of displayed symbols to:
* Red
*/

void Red_I_txt();
/**
* Function changes color of displayed symbols to:
* Bolded Red
*/

void Cyan_I_txt();
/**
* Function changes color of displayed symbols to:
* Cyan
*/

void Occupied_tile_txt();
/**
* Function changes way of displaying symbol so it looks like white rectangles:
* white background and white letter
*/

void Players_color(struct game_state* GS, int i, int j);
/**
* A function that changes color of displayed text for each player
* @param *GS - game_state
* @param i - x coordinate of a tile
* @param j - y coordinate of a tile
*/

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

void order_scores(int number_of_players, player_data player[], player_data ranking[] )
/* 
* Creates a new structure by copying the player structure
* sorts a new structure by the number of points
* @param number_of_players - number of players in the game
* @param player[] - old structure
* @param ranking - new strucutre
*/


#endif // _Output_H