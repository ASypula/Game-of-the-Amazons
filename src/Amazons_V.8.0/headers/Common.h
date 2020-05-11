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

typedef struct tile {
    int treasure;
    int artifact;
    int occupation;
}tile;

typedef struct player_data {
    char name[NAME_LENGTH];
    int ID;
    int points;
}player_data;

typedef struct coordinate {
    int x;
    int y;
}coordinate;

typedef struct variable{
    int width;
    int height;
    int number_of_players;
    int number_of_pawns;
}variable;

typedef struct game_state {
    tile** board;
    player_data* player_list;
    coordinate point_1;
    coordinate point_2;
    variable fixed;
    int current_player;
    int n_player;
    int p_with_valid_moves;
    int* still_in_game;
    int c;
}game_state;
/*
        DATA STRUCTURE OF THE GAME

    TILE:   (Structure defining each tile of the board)

        int treasure    -   value of treasure on tile
        int artifact    -   value of artifact on a tile
        int occupation  -   ID of players/element on a tile

    PLAYER_DATA: (Structure defining a information of each player)

        char name[] -   Name of player 
        int ID      -   Id of this player
        int points  -   Points of this player

    COORDINATE: (Structure defining a coordinate of a point)

        x - x coordinate of the point
        y - y coordinate of the point

    VARIABLE:   (Structure defining a data fixed by players)

        int width               - width of the board
        int height              - height of the board
        int number_of_players   - how many players play the game
        int number_of_pawns     - how many pawns each players have

    GAME_STATE: (Whole strcutre of the game)

        tile** board                - array of tiles (board)
        player_data* player_list    - list of players
        coordinate point_1          - coordinates of a point 1
        coordinate point_2          - coordinates of a point 2
        variable fixed              - variable fixed by player
        int current_player          - id of player currently making move
        int n_player                - n-th player
        int p_with_valid_moves      - how many players still can make a move
        int still_in_game           - how many players are still playing
        int c                       - currently stored character

*/

void blank_table(int table, int size);
/* fills the table with 0's
    table - chosen table to work on
    size - size of the table*/

int get_next(int* c);
/* function that gets next char after whitespaces
    *c - currently stored character (the one previously taken)*/

int number(int x);
/* changes a number from ASCII code to the decimal number
    x - number in ASCII code
    return value - a corresponding decimal number */

#endif // _Common_H