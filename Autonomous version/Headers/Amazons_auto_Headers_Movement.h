#ifndef _Movement_H
#define _Movement_H

#include "Common.h"


void find_amazons (game_state* GS);
/**
* finding its own amazons on the board and saving their positions
* saves the number of our already placed pawns
* @param *GS - game_state
*/

void choose_amazon(game_state* GS, int* x, int* y, int *n_amazon);
/**
* programme chooses an amazon that can get the highest available treasure
* function also checks if the chosen amazon belongs to current player and whether it has valid moves
* @param *GS - game_state
* @param *x  - x coordinate
* @param *y  - y coordinate
* @param *n_amazon - amazon with a path with the highest treasure
*/

void get_treasure(game_state* GS, int x, int y);
/**
* gives the treasure to the player (adds the number to the score of current player), deletes it from the board
* @param *GS - game_state
* @param x - x coordinate
* @param y - y coordinate
* (x, y) - tile from which an amazon gets the treasure
*/

int point_in_board (game_state* GS, int x, int y);
/**
* checks if given point is inside the board
* @param *GS - game_state
* @param x  - x coordinate
* @param y  - y coordinate
* @return 1 if the point is inside the board, 0 if the point is outside
*/

int is_occupied(game_state* GS, int x, int y);
/**
* checks whether a tile is occupied (free) or not
* @param *GS - game_state
* @param x - x coordinate
* @param y - y coordinate
* @return 1 if tile is occupied, 0 if it is free
*/

int max_points_line (game_state* GS, int p, int q, int *dx, int *dy, int n_amazon);
/**
* returns the maximum treasure that is available in one line
* @param *GS - game_state
* @param p - variable = -1, 0, 1 (depending on which line we check)
* @param q  - variable = -1, 0, 1 (depending on which line we check)
* for example if we check the line to the left of the amazon p = -1 and q = 0
* @param *dx - x coordinate of a tile with the highest treasure
* @param *dy - y coordinate of a tile with the highest treasure
* @param n_amazon - number of the amazon that is being checked
* @return value of the maximum treasure available for the amazon in one line
*/

int max_points_tile (game_state* GS, int *x, int *y, int n_amazon);
/**
* saves the coordinates (x, y) of a tile with maximum number of points (available for the player)
* @param *GS - game_state
* @param *x  - x coordinate
* @param *y  - y coordinate
* @param n_amazon - number of the amazon that is being checked
* @return -1 if the amazon cannot make a move or otherwise the maximum value of available treasure
*/

int tile_with_enemy (game_state* GS, int x, int y);
/**
* checks if on a given tile is placed different player's amazon
* @param *GS - game_state
* @param x - x coordinate
* @param y - y coordinate
* @return 1 if the tile is occupied by a different amazon, 0 otherwise
*/

int line_with_enemy (game_state* GS, int p, int q, int *dx, int *dy, int n_amazon);
/**
* checks if an enemy is located on an accessible line
* @param *GS - game_state
* @param p - variable = -1, 0, 1 (depending on which line we check)
* @param q  - variable = -1, 0, 1 (depending on which line we check)
* for example if we check the line to the left of the amazon p = -1 and q = 0
* @param *dx - x coordinate of a tile with the highest treasure
* @param *dy - y coordinate of a tile with the highest treasure
* @param n_amazon - number of the amazon that is being checked
* @return 1 if enemy is on the line, 0 if there is not
*/

int tile_with_closest_enemy (game_state* GS, int *x, int *y, int n_amazon);
/**
* checks if there exists an accessible line to an enemy
* @param *GS - game_state
* @param *x - x coordinate
* @param *y - y coordinate
* @param n_amazon - number of the amazon that is being checked
* @return 1 if there exists a line to the enemy, 0 if it does not
*/

int valid_path_for_arrow(game_state* GS, int *dx, int *dy, int p, int q, int n_amazon);
/**
* checks if a missile can be shot on the line
* @param *GS - game_state
* @param p - variable = -1, 0, 1 (depending on which line we check)
* @param q  - variable = -1, 0, 1 (depending on which line we check)
* for example if we check the line to the left of the amazon p = -1 and q = 0
* @param *dx - x coordinate of a tile with the highest treasure
* @param *dy - y coordinate of a tile with the highest treasure
* @param n_amazon - number of the amazon that is being checked
* @return 1 if there is a free tile on the line, 0 if there is not
*/

int random_arrow (game_state* GS, int *x, int *y, int n_amazon);
/**
* checks if an arrow can be shot
* @param *GS - game_state
* @param *x - x coordinate
* @param *y - y coordinate
* @param n_amazon - number of the amazon that is being checked
* @return 1 if the arrow can be shot, 0 if it cannot
*/

int random_spear (game_state* GS, int *x, int *y, int n_amazon);
/**
* checks if a spear can be shot
* @param *GS - game_state
* @param *x - x coordinate
* @param *y - y coordinate
* @param n_amazon - number of the amazon that is being checked
* @return 1 if the spear can be shot, 0 if it cannot
*/

void shoot_arrow(game_state* GS, int* n_amazon);
/**
* enables the amazon to shoot an arrow (with valid path), updates the board with missile's position
* @param *GS - game_state
* @param *n_amazon - number of the moving amazon
*/

void shoot_spear(game_state* GS, int* n_amazon);
/**
* enables the amazon to shoot a spear (with valid path), updates the board with missile's position
* @param *GS - game_state
* @param *n_amazon - number of the moving amazon
*/

int move_amazon(game_state* GS);
/**
* enables moving an amazon: includes functions for choosing the amazon, moving it and continuing the move depending on the artifact
* @param *GS - game_state
* @return 1 if an amazon can make a valid move, 0 if no amazon can make a move
*/


#endif // _Movement_H

