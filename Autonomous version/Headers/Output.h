#ifndef _Output_H
#define _Output_H

#include <stdio.h>
#include "Movement.h"
#include "Input.h"
#include "Common.h"
#include "Output.h"


void add_player_data_file(FILE* fp, struct game_state* GS);
/**
* Saves in file data about player_data
* @param *fp - file pointer
* @param *GS - game_state
*/

void add_size_file(FILE* fp, struct game_state* GS);
/**
* Saves in file data about size
* @param *fp - file pointer
* @param *GS - game_state
*/

void add_tiles_file(FILE* fp, struct game_state* GS);
/**
* Saves in file data about files
* @param *fp - file pointer
* @param *GS - game_state
*/

void save_data_file(char* file_name, struct game_state* GS);
/**
* Saves in file stored data from a game_state
* @param *file_name - name of the file
* @param *GS - game_state
*/

int ac_used_horses(struct game_state* GS, struct game_state* TEST);
/**
* Function counts how many horses artifact were used in this turn
* @param struct game_state* - GS - actual_game_state
* @param struct game_state* - TEST - game_state from the previous turn
*/

int ac_used_broken_arrows(struct game_state* GS, struct game_state* TEST);
/**
* Function counts how many broken arrows artifacts were used in this turn
* @param struct game_state* - GS - actual_game_state
* @param struct game_state* - TEST - game_state from the previous turn
*/

void ac_points_check(struct game_state* GS, struct game_state* TEST, int used_horse);
/**
* Function checks if any of player cheated scores
* @param struct game_state* - GS - actual_game_state
* @param struct game_state* - TEST - game_state from the previous turn
* @aparam int - used_horse - used horses in this turn
*/

void ac_arrow_check(struct game_state* GS, struct game_state* TEST, int used_horse, int used_broken_arrow);
/**
* Function checks if there is correct amount of arrows on the board
* @param struct game_state* - GS - actual_game_state
* @param struct game_state* - TEST - game_state from the previous turn
* @aparam int - used_horse - used horses in this turn
* @param int - used_broken_arrow - used broken arrows in this turn
*/

int ac_pawn_positions(struct game_state* GS, struct game_state* TEST, struct coordinate* position_now, struct coordinate* position_AC, int i);
/**
* Function saves positions of defined player pawns
* @param struct game_state* - GS - actual_game_state
* @param struct game_state* - TEST - game_state from the previous turn
* @param struct coordinate* - position_now - positions from actual game state
* @param struct coodrinate* - position_AC - position from last turn
* @param int - i - current player [ID + 1]
*/

int ac_horizontal_move(struct game_state* GS, struct coordinate* position_now, struct coordinate* position_AC, int j, int l);
/**
* Function checks if move was possible horizontally
* @param struct game_state* - GS - actual_game_state
* @param struct game_state* - TEST - game_state from the previous turn
* @param struct coordinate* - position_now - positions from actual game state
* @param struct coodrinate* - position_AC - position from last turn
* @param int - j - current pawn
* @param int - l - current checked position
*/

int ac_vertical_move(struct game_state* GS, struct coordinate* position_now, struct coordinate* position_AC, int j, int l);
/**
* Function checks if move was possible vertically
* @param struct game_state* - GS - actual_game_state
* @param struct game_state* - TEST - game_state from the previous turn
* @param struct coordinate* - position_now - positions from actual game state
* @param struct coodrinate* - position_AC - position from last turn
* @param int - j - current pawn
* @param int - l - current checked position
*/

int ac_diagonal_move(struct game_state* GS, struct coordinate* position_now, struct coordinate* position_AC, int j, int k);
/**
* Function checks if move was possible diagonally
* @param struct game_state* - GS - actual_game_state
* @param struct game_state* - TEST - game_state from the previous turn
* @param struct coordinate* - position_now - positions from actual game state
* @param struct coodrinate* - position_AC - position from last turn
* @param int - j - current pawn
* @param int - k - current checked position
*/

void ac_check_move(struct game_state* GS, struct game_state* TEST, struct coordinate* position_now, struct coordinate* position_AC, int i, int count);
/**
* Function checks if move of each pawn was possible
* @param struct game_state* - GS - actual_game_state
* @param struct game_state* - TEST - game_state from the previous turn
* @param struct coordinate* - position_now - positions from actual game state
* @param struct coodrinate* - position_AC - position from last turn
* @param int - i - current player
* @param int - count - how many pawns has the player
*/

void ac_system(struct game_state* GS, struct game_state* TEST);
/**
* Function checks if any of player cheated
* If not any horse was used, function checks if last move of a players was possible
* Checks if players was possible to earn that many points or hasn't lost some
* Checks if there is correct number of arrows
* @param struct game_state* - GS - actual_game_state
* @param struct game_state* - TEST - game_state from the previous turn
*/

#endif // _Output_H
