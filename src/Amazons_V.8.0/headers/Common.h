#ifndef _Common_H

#define _Common_H
#define FREE 0
#define OCCUPIED 1
#define MISSILE 9
#define MAX_NUMBER_OF_PLAYERS 8
#define NAME_LENGTH 15
#define EMPTY 0
#define HORSE 1
#define BROKEN_ARROW 2
#define SPEAR 3
#define NORMAL_MOVE 1
#define CTRL_MOVE 5
#define Starting_position 0

/**
* A structure with date of a tile
*/
typedef struct tile {
    /*@{*/
    int treasure;   /**< value of treasure on tile          */
    int artifact;   /**< value of artifact on tile          */
    int occupation; /**< ID of players/element on a tile    */
    /*@}*/
}tile;

/**
* A structure defining a information of each player
*/
typedef struct player_data {
    /*@{*/
    char name[NAME_LENGTH]; /**< Name of player (Maximal lenght of 15)      */
    int ID;                 /**< Id of player                               */
    int points;             /**< Points of earned by player                 */
    /*@}*/
}player_data;

/**
* A structure defining a coordinate of a point
*/
typedef struct coordinate {
    /*@{*/
    int x;  /**< x coordinate of the point  */
    int y;  /**< y coordinate of the point  */
    /*@}*/
}coordinate;

/**
* A structure defining a data fixed by players
*/
typedef struct fixed_inf{
    /*@{*/
    int width;              /**< width of the board                 */
    int height;             /**< height of the board                */
    int number_of_players;  /**< how many players play the game     */
    int number_of_pawns;    /**< how many pawns each players have   */
    /*@}*/
}fixed_inf;

/**
* A structure describing the state of the game
*/
typedef struct game_state {
    /*@{*/
    tile** board;               /**< array of tiles (board)                     */
    player_data* player_list;   /**< list of players                            */
    coordinate point_1;         /**< coordinates of a point 1                   */
    coordinate point_2;         /**< coordinates of a point 2                   */
    fixed_inf fixed;            /**< information fixed by player                */
    int current_player;         /**< id of player currently making move         */
    int n_player;               /**< n-th player                                */
    int p_with_valid_moves;     /**< how many players still can make a move     */
    int* still_in_game;         /**< how many players are still playing         */
    int c;                      /**< currently stored character                 */
    /*@}*/
}game_state;

void blank_table(int table, int size);
/** 
* fills the table with 0's
* @param table - chosen table to work on (to be filled with 0's)
* @param size - size of the table
*/

int get_next(int* c);
/** 
* function that gets next char after whitespaces
* @param *c - currently stored character (the one previously taken)
* @return next character
*/

int number(int x);
/** 
* changes a number from ASCII code to the decimal number
* @param x - number in ASCII code
* @return value - a corresponding decimal number
*/


#endif // _Common_H