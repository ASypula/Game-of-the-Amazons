#ifndef _Movement_H
#define _Movement_H

#include "Common.h"

void choose_amazon(game_state* GS, int* x, int* y);
/**
* player chooses an amazon to move (gives a number of row and column)
* function also checks if the chosen amazon belongs to current player and whether it has valid moves
* @param *GS - game_state
* @param *x  - x coordinate
* @param *y  - y coordinate
*/

void get_treasure(game_state* GS);
/**
* gives the treasure to the player (adds the number to the score of current player), deletes it from the board
* @param *GS - game_state
*/

void shoot_arrow(game_state* GS);
/**
* enables the amazon to shoot an arrow (with valid path), updates the board with missile's position
* @param *GS - game_state
*/

void shoot_spear(game_state* GS);
/**
* enables the amazon to shoot a spear (with valid path), updates the board with missile's position
* @param *GS - game_state
*/

void move_amazon(game_state* GS);
/**
* enables moving an amazon: includes functions for choosing the amazon, moving it and continuing the move depending on the artifact
* @param *GS - game_state
*/

int is_occupied(game_state* GS, int x, int y);
/**
* checks whether a tile is occupied (free) or not
* @param *GS - game_state
* @param x - current row
* @param y - current column
* @return 1 if tile is occupied, 0 if it is free
*/

int check_orthogonal_path_for_x(game_state* GS, int x1, int x2, int y);
/**
* checks the orthogonal path for an amazon or an arrow, when the number of a column is constant
* @param *GS - game_state
* @param x1 - current row
* @param x2 - final row
* @param y - column
* @return 1 if path is occupied, 0 if it is free
*/

int check_orthogonal_path_for_y(game_state* GS, int x, int y1, int y2);
/**
* checks the orthogonal path for an amazon or an arrow, when the number of a row is constant
* @param *GS - game_state
* @param x - row
* @param y1 - current column
* @param y2 - final column
* @return 1 if path is occupied, 0 if it is free
*/

int check_diagonal_path(game_state* GS, int x1, int x2, int y1, int y2);
/**
* checks the diagonal path for an amazon or an arrow
* @param *GS - game_state
* @param x1 - current row
* @param x2 - final row
* @param y1 - current column
* @param y2 - final column
* @return 1 if path is occupied, 0 if it is free
*/

int path_invalid(game_state* GS, int x1, int x2, int y1, int y2);
/**
* checks path for an amazon or an arrow (combines orthogonal and diagonal paths)
* @param *GS - game_state
* @param x1 - current row
* @param x2 - final row
* @param y1 - current column
* @param y2 - final column
* @return 0 = path is valid; 1 = path is not valid; -1 = it is not a move
*/

int check_corner(game_state* GS, int x, int y, int p, int q);
/**
* checks if the amazon positioned on the corner has any valid moves
* @param *GS - game_state
* @param x - current row
* @param y - current column
* @param p = +1 if the amazon is on the left, p = -1 if the amazon is on the right of the board
* @param q = +1 if the amazon is at the bottom, q = -1 if the amazon is at the top of the board
* @return 1 if the amazon does not have any valid moves, returns 0 if the amazon can make a move
*/

int check_xs(game_state* GS, int x, int y, int p);
/**
* checks if the amazon positioned on the vertical edge has any valid moves
* @param *GS - game_state
* @param x - current row
* @param y - current column
* @param p = +1 if the amazon is on the left, p = -1 if the amazon is on the right of the board
* @return 1 if the amazon does not have any valid moves, returns 0 if the amazon can make a move
*/

int check_ys(game_state* GS, int x, int y, int p);
/**
* checks if the amazon positioned on the vertical edge has any valid moves
* @param *GS - game_state
* @param x - current row
* @param y - current column
* @param p = +1 if the amazon is at the bottom, p = -1 if the amazon is at the top of the board
* @return 1 if the amazon does not have any valid moves, returns 0 if the amazon can make a move
*/

int no_more_moves(game_state* GS, int x, int y);
/**
* checks if an amazon has any valid moves
* @param *GS - game_state
* @param x - current row
* @param y - current column
* @return 1 if the amazon does not have any valid move; 0 otherwise
*/

int ending_for_a_player(game_state* GS);
/**
* checks if an amazon has any valid moves
* @param *GS - game_state
* @return if the player can make any move returns 0, if the player has to end/finish the game returns 1
*/

#endif // _Movement_H

