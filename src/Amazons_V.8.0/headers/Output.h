#ifndef _Output_H
#define _Output_H

#include "Common.h"

//Makes the text White
void White_txt();

//Makes the Bold white text
void White_bold_txt();

//Makes the text intense yellow
void Yellow_I_txt();

//Makes the text Green
void Green_txt();

//Makes the text intense green
void Green_I_txt();

//Makes the text Blue
void Blue_txt();

//Makes the text intense Blue
void Blue_I_txt();

//Makes the text Magenta
void Magenta_txt();

//Makes the text intense Magenta
void Magenta_I_txt();

//Makes the text Red
void Red_txt();

//Makes the text intense Red
void Red_I_txt();

//Makes the text intense Cyan
void Cyan_I_txt();

//Makes the tile all white which means it is occupied by arrow/spear
void Occupied_tile_txt();

//Function to check color for specific player ID (Sends Error message when ID is not valid (is not in range from 0-9))
void Players_color(struct game_state* GS, int i, int j);
/*
*GS - game_state
i - x coordinate
j - y coordinate
*/


//Filling a board with content
void generate_board(struct game_state* GS);
/*
    *GS - game_state
*/

//Function drawing given board with colors
void draw_board_color(struct game_state* GS);
/*
    *GS - game_state
*/

void order_scores(int number_of_players, player_data player[], player_data ranking[] )
/* creates a new structure by copying the player structure
sorts a new structure by the number of points*/


#endif // _Output_H