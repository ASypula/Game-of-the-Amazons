#ifndef _Common_H

#define _Common_H
#define MIN_ASCII_DIGIT 48
#define MAX_ASCII_DIGIT 57
#define FREE 0
#define OCCUPIED 1
#define MISSILE 9
#define MAX_NUMBER_OF_PLAYERS 8
#define NAME_LENGTH 16
#define EMPTY 0
#define HORSE 1
#define BROKEN_ARROW 2
#define SPEAR 3
#define NORMAL_MOVE 1
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
    char name[NAME_LENGTH]; /**< Name of player (Maximal length of 15)      */
    int ID;                 /**< Id of player                               */
    int points;             /**< Points earned by player                    */
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
    char name[NAME_LENGTH];     /**< name of our programme                      */
    tile** board;               /**< array of tiles (board)                     */
    player_data* player_list;   /**< list of players                            */
    coordinate point_1;         /**< coordinates of a point 1                   */
    coordinate point_2;         /**< coordinates of a point 2                   */
    coordinate* positions;      /**< positions of tiles occupied by the player  */
    fixed_inf fixed;            /**< information fixed by player                */
    int current_player;         /**< id of player currently making move         */
    int n_player;               /**< n-th player                                */
    int error;					/**< Does program got errors during reading file*/
    int c;                      /**< currently stored character                 */
    int already_placed_amazons; /**< number of already placed amazons           */
    /*@}*/
}game_state;

int is_digit (char c);
/**
* checks if a given character is a digit from 0 to 9 
* @param c - character being checked
* @return 1 if c is a digit, 0 otherwise
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

int fmax(int x, int y);
/**
* function returning the maximum of two values
* @param x - first value to be compared
* @param y - second value to be compared
* @return maximum of (x, y) or if they're equal then any of them
*/

int fmax_of8(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8);
/**
* function returning the maximum of two values
* @param x1 - first value to be compared
* @param x2 - second value to be compared
* @param x3 - third value to be compared
* @param x4 - forth value to be compared
* @param x5 - fifth value to be compared
* @param x6 - sixth value to be compared
* @param x7 - seventh value to be compared
* @param x8 - eighth value to be compared
* @return maximum of eight values or if they're equal then any of them
*/

#endif // _Common_H
