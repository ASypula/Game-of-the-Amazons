#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
#define TRUE 1
#define FALSE 0

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
typedef struct fixed_inf {
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
    char* name;                 /**< name of our programme                      */
    tile** board;               /**< array of tiles (board)                     */
    player_data* player_list;   /**< list of players                            */
    coordinate point_1;         /**< coordinates of a point 1                   */
    coordinate point_2;         /**< coordinates of a point 2                   */
    coordinate* positions;      /**< positions of tiles occupied by the player  */
    fixed_inf fixed;            /**< information fixed by player                */
    int current_player;         /**< id of player currently making move         */
    int n_player;               /**< n-th player                                */
    int error;					/**< Does program got errors during reading file*/
    int already_placed_amazons; /**< number of already placed amazons           */
    /*@}*/
}game_state;



int is_digit(char c)
{
    if (c >= MIN_ASCII_DIGIT && c <= MAX_ASCII_DIGIT)
        return 1;
    else
        return 0;
}

int number(int x)
{
    x = x - '0';
    return x;
}

int find_ID(game_state* GS)
{
    int i = 0;
    while (strcmp(GS->player_list[i].name, GS->name))
    {
        i++;
    }
    return GS->player_list[i].ID;
}

int find_max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int fmax_of8(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8)
{
    int max_x;
    max_x = find_max(find_max(find_max(x1, x2), find_max(x3, x4)), find_max(find_max(x5, x6), find_max(x7, x8)));
    return max_x;
}

int point_in_board(game_state* GS, int x, int y)
{
    if ((x >= 0) && (y >= 0) && (x < GS->fixed.height) && (y < GS->fixed.width))
        return 1;
    else
        return 0;
}

void print_board(game_state* GS)
{
    int i, j;
    for (i = 0; i < GS->fixed.height; i++)
    {
        for (j = 0; j < GS->fixed.width; j++)
            printf("%d%d%d ", GS->board[i][j].treasure, GS->board[i][j].artifact, GS->board[i][j].occupation);
        printf("\n");
    }
}

int get_multi_digit_file(FILE* fp, game_state* GS) {

    int c;
    char buffer[12]; // Max 10 digit number
    int count = 0;
    int number;

    do {
        c = getc(fp);

        if (c != '\n' && c != ' ' && c != EOF) {
            if (count >= 11) {
                printf("Error! Size number has more that 10 digits, unable to read!\n");
                GS->error = 1;
            }

            buffer[count++] = (char)c;
        }
        else if (count > 0) {
            buffer[count] = 0;

            number = atoi(buffer);
            if (number < 0) {
                printf("Error! Size number is negative!\n");
                GS->error = 1;
            }

            count = 0;
        }
    } while (c != '\n' && c != ' ' && c != EOF);

    return number;
}

tile get_tile_file(FILE* fp, struct game_state* GS, int i, int j) {

    tile temp;
    int c;
    int buffer[10]; // 3 digit tile
    int count = 0;

    do {
        c = getc(fp);

        if (c != ' ' && c != '\n' && c != EOF) {
            if (count >= 3) {
                //Exception
                printf("Error in reading tile[%d][%d], tile has more than 3 digits!\n", i, j);
                GS->error = 1;
            }

            buffer[count++] = c;
        }
        else if (count > 0) {

            temp.treasure = number(buffer[0]);
            if (temp.treasure > 5 || temp.treasure < 0) {
                printf("Error in reading tile[%d][%d], wrong value of treasure tile!\n", i, j);
                GS->error = 1;
            }
            temp.artifact = number(buffer[1]);
            if (temp.artifact > 3 || temp.artifact < 0) {
                printf("Error in reading tile[%d][%d], wrong value of artifact tile!\n", i, j);
                GS->error = 1;
            }
            temp.occupation = number(buffer[2]);
            if (temp.occupation > 9 || temp.occupation < 0) {
                printf("Error in reading tile[%d][%d], wrong value of occupation tile!\n", i, j);
                GS->error = 1;
            }
            if ((temp.occupation > 0 && temp.occupation < 9) && (temp.treasure != 0 || temp.artifact != 0)) {
                printf("Occupied Tile[%d][%d], has: ", i, j);
                if (temp.treasure != 0) {
                    printf("treasure=%d ", temp.treasure);
                }
                if (temp.artifact != 0) {
                    printf("artifact=%d ", temp.artifact);
                }
                printf("\n");
                GS->error = 1;
            }
            count = 0;
        }
    } while (c != ' ' && c != '\n' && c != EOF);

    return temp;
}

void get_board_file(FILE* fp, struct game_state* GS) {

    int i, j;
    for (i = 0; i < GS->fixed.height; i++) {
        for (j = 0; j < GS->fixed.width; j++) {
            GS->board[i][j] = get_tile_file(fp, GS, i, j);
        }
    }
}

void get_player_data_file(FILE* fp, struct game_state* GS) {

    int c;
    int count = 0;
    int lines = 0;
    int type = 0; // 0 - name, 1 - ID, 2 - points
    char bufor[16];

    do {

        c = getc(fp);

        if (c != ' ' && c != '\n' && c != EOF) {

            if (type == 0 && count >= 15) {
                printf("Error! Read name has more that 15 chars!\n");
                GS->error = 1;
            }

            if (type == 2 && count >= 15) {
                printf("Error! Points number has more than 15 digits, unable to read!\n");
                GS->error = 1;
            }

            if (type == 0) {
                GS->player_list[lines].name[count++] = (char)c;
            }
            else if (type == 1 || type == 2) {
                bufor[count++] = (char)c;
                if (c < 48 || c > 57) {
                    printf("Error! Score of a player cointains a char!\n");
                    GS->error = 1;
                }
            }

        }
        else if (count > 0) {

            if (type == 0) {
                GS->player_list[lines].name[count] = 0; // Null at the end of a string
                type = 1;
            }
            else if (type == 1) {
                bufor[count] = 0;
                GS->player_list[lines].ID = atoi(bufor);
                if (GS->player_list[lines].ID < 0 || GS->player_list[lines].ID > 8) {
                    printf("Error! Wrong value of player ID!\n");
                    GS->error = 1;
                }
                type = 2;
            }
            else if (type == 2) {
                bufor[count] = 0;
                GS->player_list[lines].points = atoi(bufor);
                if (GS->player_list[lines].ID < 0) {
                    printf("Error! Negative value of player's points!\n");
                    GS->error = 1;
                }
                type = 0;
                lines++;
            }

            count = 0;
        }

    } while (c != EOF);

    GS->fixed.number_of_players = lines;

    int i, j;
    for (i = 0; i < GS->fixed.height; i++) {
        for (j = 0; j < GS->fixed.width; j++) {
            if (GS->board[i][j].occupation > GS->fixed.number_of_players&& GS->board[i][j].occupation != MISSILE) {
                printf("Boards contains a pawn of undeclared player! ID:%d, Tile:[%d][%d]\n", GS->board[i][j].occupation, i, j);
                GS->error = 1;
            }
        }
    }
}

void add_user_initation(struct game_state* GS) {

    int i;
    int on_list = 0;

    for (i = 0; i < GS->fixed.number_of_players; i++) {
        if (!strcmp(GS->name, GS->player_list[i].name)) {
            on_list = 1;
        }
    }

    i = 0;
    if (!on_list) {
        while (GS->name[i]) {
            GS->player_list[GS->fixed.number_of_players].name[i] = GS->name[i];
            i++;
        }
        GS->player_list[GS->fixed.number_of_players].name[i] = 0;
        //GS->player_list[GS->fixed.number_of_players].name = GS->name;
        GS->player_list[GS->fixed.number_of_players].ID = (GS->fixed.number_of_players + 1);
        GS->player_list[GS->fixed.number_of_players].points = 0;

        GS->fixed.number_of_players++;
    }
}

void read_file(char* file_name, struct game_state* GS) {

    FILE* fp = fopen(file_name, "r+");

    if (fp == NULL) {
        printf("Error in opening file!");
        GS->error = 1;
    }
    else {

        // HEIGHT

        GS->fixed.height = get_multi_digit_file(fp, GS);

        // WIDTH

        GS->fixed.width = get_multi_digit_file(fp, GS);

        // ALLOCATING MEMORY FOR THE BOARD

        GS->board = malloc(GS->fixed.height * sizeof(**(GS->board)));
        int p = 0;
        while (p < GS->fixed.height) {
            *(GS->board + p) = malloc(GS->fixed.width * sizeof(**(GS->board)));
            p++;
        }

        // ALLOCATING MEMORY FOR THE PLAYER_DATA

        GS->player_list = (player_data*)malloc(sizeof(player_data) * 8);

        // BOARD

        get_board_file(fp, GS);

        // PLAYER DATA

        get_player_data_file(fp, GS);

        //Adding name if needed

        add_user_initation(GS);

        fclose(fp);
    }
}


int is_occupied(game_state* GS, int x, int y)
{
    if (GS->board[x][y].occupation != FREE)
        return OCCUPIED;
    else
        return FREE;
}

int found_horse(game_state* GS, int* dx, int* dy, int x, int y) {
    int found = 0;
    int i, j;
    if (x == 0)
    {
        for (i = 0; (i < GS->fixed.height) && !found; i++)
        {
            for (j = 0; (j < GS->fixed.width) && !found; j++)
            {
                if (GS->board[i][j].artifact == HORSE)
                {
                    *dx = i;
                    *dy = j;
                    found = 1;
                }
            }
        }
    }
    else
    {
        for (j = y; (j < GS->fixed.width) && !found; j++)
        {
            if (GS->board[x][j].artifact == HORSE)
            {
                *dx = x;
                *dy = j;
                found = 1;
            }
        }
        for (i = x + 1; (i < GS->fixed.height) && !found; i++)
        {
            for (j = 0; (j < GS->fixed.width) && !found; j++)
            {
                if (GS->board[i][j].artifact == HORSE)
                {
                    *dx = i;
                    *dy = j;
                    found = 1;
                }
            }
        }
    }
    return found;
}

int check_orthogonal_path_for_x(game_state* GS, int x1, int x2, int y)
{
    int occupation = FREE;
    if (x1 < x2)
    {
        x1++;
        while ((x1 <= x2) && (occupation == FREE))
        {
            occupation = is_occupied(GS, x1, y);
            x1++;
        }
        return occupation;
    }
    else
    {
        x1--;
        while ((x1 >= x2) && (occupation == FREE))
        {
            occupation = is_occupied(GS, x1, y);
            x1--;
        }
        return occupation;
    }
}


int check_orthogonal_path_for_y(game_state* GS, int x, int y1, int y2)
{
    int occupation = FREE;
    if (y1 < y2)
    {
        y1++;
        while ((y1 <= y2) && (occupation == FREE))
        {
            occupation = is_occupied(GS, x, y1);
            y1++;
        }
        return occupation;

    }
    else
    {
        y1--;
        while ((y1 >= y2) && (occupation == FREE))
        {
            occupation = is_occupied(GS, x, y1);
            y1--;
        }
        return occupation;
    }
}

int check_diagonal_path(game_state* GS, int x1, int x2, int y1, int y2)
{
    int occupation = FREE;
    if (x1 < x2 && y1 < y2)
    {
        x1++;
        y1++;
        while (x1 <= x2 && y1 <= y2 && (occupation == FREE))
        {
            occupation = is_occupied(GS, x1, y1);
            x1++;
            y1++;
        }
        x1--;
        y1--;
    }
    else if (x1 < x2 && y1 > y2)
    {
        x1++;
        y1--;
        while (x1 <= x2 && y1 >= y2 && (occupation == FREE))
        {
            occupation = is_occupied(GS, x1, y1);
            x1++;
            y1--;
        }
        x1--;
        y1++;
    }
    else if (x1 > x2&& y1 < y2)
    {
        x1--;
        y1++;
        while (x1 >= x2 && y1 <= y2 && (occupation == FREE))
        {
            occupation = is_occupied(GS, x1, y1);
            x1--;
            y1++;
        }
        x1++;
        y1--;
    }
    else if (x1 > x2&& y1 > y2)
    {
        x1--;
        y1--;
        while (x1 >= x2 && y1 >= y2 && (occupation == FREE))
        {
            occupation = is_occupied(GS, x1, y1);
            x1--;
            y1--;
        }
        x1++;
        y1++;
    }
    if ((x1 == x2) && (y1 == y2))
        return occupation;
    else /* the path is not a straight line */
        return OCCUPIED;
}

int path_invalid(game_state* GS, int x1, int x2, int y1, int y2)
{
    int occupation = FREE;
    if (x1 != x2)
    {
        if (y1 != y2)
        {
            occupation = check_diagonal_path(GS, x1, x2, y1, y2);
        }
        else
            occupation = check_orthogonal_path_for_x(GS, x1, x2, y1);
    }
    else
    {
        if (y1 != y2)
            occupation = check_orthogonal_path_for_y(GS, x1, y1, y2);
        else /* x1 = x2, y1 = y2 */
        {
            occupation = OCCUPIED;
        }
    }
    return occupation;
}

int path_to_horse(game_state* GS, int* dx, int* dy, int n_amazon)
{
    int no_horse = 1;
    int x1 = GS->positions[n_amazon].x;
    int y1 = GS->positions[n_amazon].y;
    int x2 = 0;
    int y2 = 0;
    while (no_horse && point_in_board(GS, x2, y2) && found_horse(GS, dx, dy, x2, y2))
    {
        if (path_invalid(GS, x1, *dx, y1, *dy))
        {
            if (*dy == (GS->fixed.width - 1))
            {
                (*dx)++;
                *dy = -1;
            }
            x2 = *dx;
            y2 = *dy + 1;
        }
        else
        {
            no_horse = 0;
        }
    }
    if (no_horse == 0)
        return 1;
    else
        return 0;
}

int max_point(game_state* GS, int* dx, int* dy, int x, int y, int search_max)
{
    int i, j;
    int max_found = 0;
    for (i = x; (i < GS->fixed.height) && (!max_found); i++)
    {
        for (j = y; (j < GS->fixed.width) && (!max_found); j++)
        {
            if (GS->board[i][j].treasure == search_max)
            {
                *dx = i;
                *dy = j;
                max_found = 1;
            }
        }
    }
    if (!max_found)
    {
        *dx = i;
        *dy = j;
    }
    return max_found;
}


int max_points_line(game_state* GS, int p, int q, int* dx, int* dy, int n_amazon)
{
    int points = 0;
    int x = GS->positions[n_amazon].x;
    int y = GS->positions[n_amazon].y;
    x += p;
    y += q;
    while (point_in_board(GS, x, y) && !is_occupied(GS, x, y))
    {
        if (GS->board[x][y].treasure >= points)
        {
            points = GS->board[x][y].treasure;
            *dx = x;
            *dy = y;
        }
        x += p;
        y += q;
    }
    if ((x - p) == GS->positions[n_amazon].x && (y - q) == GS->positions[n_amazon].y)
        return -1;
    else
        return points;
}

int max_points_tile(game_state* GS, int* x, int* y, int n_amazon)
{
    int max_points;
    int left = max_points_line(GS, 0, -1, x, y, n_amazon);
    int left_up = max_points_line(GS, -1, -1, x, y, n_amazon);
    int up = max_points_line(GS, -1, 0, x, y, n_amazon);
    int right_up = max_points_line(GS, -1, 1, x, y, n_amazon);
    int right = max_points_line(GS, 0, 1, x, y, n_amazon);
    int right_down = max_points_line(GS, 1, 1, x, y, n_amazon);
    int down = max_points_line(GS, 1, 0, x, y, n_amazon);
    int left_down = max_points_line(GS, 1, -1, x, y, n_amazon);
    max_points = fmax_of8(left, left_up, up, right_up, right, right_down, down, left_down);
    if (max_points != -1)
    {
        if (max_points == left)
        {
            max_points = max_points_line(GS, 0, -1, x, y, n_amazon); //just to remember the place of the tile with max points
        }
        else if (max_points == left_up)
        {
            max_points = max_points_line(GS, -1, -1, x, y, n_amazon);
        }
        else if (max_points == up)
        {
            max_points = max_points_line(GS, -1, 0, x, y, n_amazon);
        }
        else if (max_points == right_up)
        {
            max_points = max_points_line(GS, -1, 1, x, y, n_amazon);
        }
        else if (max_points == right)
        {
            max_points = max_points_line(GS, 0, 1, x, y, n_amazon);
        }
        else if (max_points == right_down)
        {
            max_points = max_points_line(GS, 1, 1, x, y, n_amazon);
        }
        else if (max_points == down)
        {
            max_points = max_points_line(GS, 1, 0, x, y, n_amazon);
        }
        else if (max_points == left_down)
        {
            max_points = max_points_line(GS, 1, -1, x, y, n_amazon);
        }
        return max_points;
    }
    else
        return -1;
}

int valid_path_for_arrow(game_state* GS, int p, int q, int* dx, int* dy, int n_amazon)
{
    int x = GS->positions[n_amazon].x;
    int y = GS->positions[n_amazon].y;
    x += p;
    y += q;
    while (point_in_board(GS, x, y) && !is_occupied(GS, x, y))
    {
        x += p;
        y += q;
    }
    if (x == (GS->positions[n_amazon].x + p) && y == (GS->positions[n_amazon].y + q))
        return 0;
    else
    {
        *dx = x - p;
        *dy = y - q;
        return 1;
    }
}


int random_arrow(game_state* GS, int* x, int* y, int n_amazon)
{
    if (valid_path_for_arrow(GS, 0, -1, x, y, n_amazon))      //left
        return 1;
    else if (valid_path_for_arrow(GS, -1, -1, x, y, n_amazon))//left-up
        return 1;
    else if (valid_path_for_arrow(GS, -1, 0, x, y, n_amazon)) //up
        return 1;
    else if (valid_path_for_arrow(GS, -1, 1, x, y, n_amazon)) //right-up
        return 1;
    else if (valid_path_for_arrow(GS, 0, 1, x, y, n_amazon))  //right
        return 1;
    else if (valid_path_for_arrow(GS, 1, 1, x, y, n_amazon))  //right-down
        return 1;
    else if (valid_path_for_arrow(GS, 1, 0, x, y, n_amazon))  //down
        return 1;
    else if (valid_path_for_arrow(GS, 1, -1, x, y, n_amazon)) //left-down
        return 1;
    else
        return 0;
}

//spear can go through a missile
int random_spear(game_state* GS, int* x, int* y, int n_amazon)
{
    if (valid_path_for_arrow(GS, 0, -1, x, y, n_amazon))      //left
        return 1;
    else if (valid_path_for_arrow(GS, -1, -1, x, y, n_amazon))//left-up
        return 1;
    else if (valid_path_for_arrow(GS, -1, 0, x, y, n_amazon)) //up
        return 1;
    else if (valid_path_for_arrow(GS, -1, 1, x, y, n_amazon)) //right-up
        return 1;
    else if (valid_path_for_arrow(GS, 0, 1, x, y, n_amazon))  //right
        return 1;
    else if (valid_path_for_arrow(GS, 1, 1, x, y, n_amazon))  //right-down
        return 1;
    else if (valid_path_for_arrow(GS, 1, 0, x, y, n_amazon))  //down
        return 1;
    else if (valid_path_for_arrow(GS, 1, -1, x, y, n_amazon)) //left-down
        return 1;
    else
        return 0;
}


int tile_available(game_state* GS, int x, int y, int* found_x, int* found_y)
{
    if (point_in_board(GS, x - 1, y) && GS->board[x - 1][y].occupation == FREE)
    {
        *found_x = x - 1;
        *found_y = y;
        return 1;
    }
    else if (point_in_board(GS, x - 1, y - 1) && GS->board[x - 1][y - 1].occupation == FREE)
    {
        *found_x = x - 1;
        *found_y = y - 1;
        return 1;
    }
    else if (point_in_board(GS, x, y - 1) && GS->board[x][y - 1].occupation == FREE)
    {
        *found_x = x;
        *found_y = y - 1;
        return 1;
    }
    else if (point_in_board(GS, x + 1, y - 1) && GS->board[x + 1][y - 1].occupation == FREE)
    {
        *found_x = x + 1;
        *found_y = y - 1;
        return 1;
    }
    else if (point_in_board(GS, x + 1, y) && GS->board[x + 1][y].occupation == FREE)
    {
        *found_x = x + 1;
        *found_y = y;
        return 1;
    }
    else if (point_in_board(GS, x + 1, y + 1) && GS->board[x + 1][y + 1].occupation == FREE)
    {
        *found_x = x + 1;
        *found_y = y + 1;
        return 1;
    }
    else if (point_in_board(GS, x, y + 1) && GS->board[x][y + 1].occupation == FREE)
    {
        *found_x = x;
        *found_y = y + 1;
        return 1;
    }
    else if (point_in_board(GS, x - 1, y + 1) && GS->board[x - 1][y - 1].occupation == FREE)
    {
        *found_x = x - 1;
        *found_y = y + 1;
        return 1;
    }
    else
        return 0;
}

int best_place(game_state* GS, int* found_x, int* found_y)
{
    int x, y;
    if (GS->already_placed_amazons == 0)
    {
        x = 0;
        y = 0;
    }
    else
    {
        x = GS->positions[GS->already_placed_amazons - 1].x + 1;
        y = GS->positions[GS->already_placed_amazons - 1].y + 1;
    }
    int* dx;
    dx = (int*)malloc(sizeof(int));
    int* dy;
    dy = (int*)malloc(sizeof(int));
    *dx = x;
    *dy = y;
    int max_search = 5;  //maximum value of treasure
    int no_place = 1;
    while (no_place && found_horse(GS, dx, dy, x, y))
    {
        if (!(tile_available(GS, *dx, *dy, found_x, found_y)))
        {
            if (*dx >= GS->fixed.height)
            {
                *dx = -1;
                (*dy)++;
            }
            x = *dx + 1;
            y = *dy;
        }
        else
        {
            no_place = 0;
        }
    }
    if (no_place)
    {
        while (no_place)
        {
            while (max_search >= 0 && !max_point(GS, dx, dy, x, y, max_search))
            {
                if ((*dx == GS->fixed.height) && (*dy == GS->fixed.width))
                {
                    x = *dx = 0;
                    y = *dy = 0;
                    max_search--;
                }
                else if (*dx = GS->fixed.height)
                {
                    *dx = 0;
                    *dy++;
                }
                else
                {
                    x = *dx + 1;
                    y = *dy;
                }
            }
            if (max_point(GS, dx, dy, x, y, max_search) && tile_available(GS, *dx, *dy, found_x, found_y) && max_search > 0)
                no_place = 0;
            else
            {
                if (*dx >= GS->fixed.height)
                {
                    *dx = -1;
                    *dy++;
                }
                x = *dx + 1;
                y = *dy;
            }
        }
    }
    if (no_place)
        return 0;
    else
        return 1;
}

void find_amazons(game_state* GS)
{
    int id = find_ID(GS);
    int placed_pawns = 0;
    int i, j;
    GS->positions = (coordinate*)malloc(sizeof(coordinate));
    for (i = 0; i < GS->fixed.height; i++) {
        for (j = 0; j < GS->fixed.width; j++) {
            if (GS->board[i][j].occupation == id) {
                GS->positions = (coordinate*)realloc(GS->positions, (placed_pawns + 1) * sizeof(coordinate));
                GS->positions[placed_pawns].x = i;
                GS->positions[placed_pawns].y = j;
                placed_pawns++;
            }
        }
    }
    GS->already_placed_amazons = placed_pawns;
}

int place_amazons(game_state* GS) {

    int id = find_ID(GS);
    int* x;
    x = (int*)malloc(sizeof(int));
    int* y;
    y = (int*)malloc(sizeof(int));
    find_amazons(GS);

    if (GS->already_placed_amazons < GS->fixed.number_of_pawns) {
        if (best_place(GS, x, y))
        {
            GS->board[*x][*y].treasure = FREE;
            GS->board[*x][*y].artifact = FREE;
            GS->board[*x][*y].occupation = id;
            GS->already_placed_amazons++;
            return 1;
        }
        else
        {
            printf("There is no valid tile to place an amazon.\n");
            return 0;
        }
    }
    else
    {
        printf("All amazons are already placed on the board.\n");
        return 0;
    }
}


int choose_amazon(game_state* GS, int* x, int* y, int* n_amazon)
{
    find_amazons(GS);
    int left_amazons = GS->already_placed_amazons - 1; //number of amazons that are left to be checked - 1
    int max_points = -1;
    int max_part;
    int* x1, * y1;
    int is_horse = 0;
    x1 = (int*)malloc(sizeof(int));
    y1 = (int*)malloc(sizeof(int));
    while (left_amazons >= 0 && !is_horse)
    {
        if (path_to_horse(GS, x1, y1, left_amazons))
        {
            *x = *x1;
            *y = *y1;
            *n_amazon = left_amazons;
            max_points = 0;
            is_horse = 1;
        }
        else if (max_points < (max_part = max_points_tile(GS, x1, y1, left_amazons)))
        {
            max_points = max_part;
            *x = *x1;
            *y = *y1;
            *n_amazon = left_amazons;
        }
        left_amazons = left_amazons - 1;
    }
    if (max_points == -1) //all amazons are blocked
    {
        printf("All amazons are blocked.\n");
        return 0;
    }
    else
        return 1;
}

int choose_after_horse(game_state* GS, int* x, int* y, int n_amazon)
{
    int max_points = -1;
    int max_part;
    int* x1, * y1;
    int is_horse = 0;
    x1 = (int*)malloc(sizeof(int));
    y1 = (int*)malloc(sizeof(int));
    if (path_to_horse(GS, x1, y1, n_amazon))
    {
        *x = *x1;
        *y = *y1;
        max_points = 0;
    }
    else if (max_points < (max_part = max_points_tile(GS, x1, y1, n_amazon)))
    {
        max_points = max_part;
        *x = *x1;
        *y = *y1;
    }
    if (max_points == -1) //all amazons are blocked
    {
        printf("The amazon is blocked.\n");
        return 0;
    }
    else
        return 1;
}


void get_treasure(game_state* GS, int x, int y)
{
    if (GS->board[x][y].treasure != 0)
    {
        GS->player_list[find_ID(GS) - 1].points += GS->board[x][y].treasure;
        GS->board[x][y].treasure = FREE;
    }
}

void shoot_arrow(game_state* GS, int n_amazon)
{
    int* x;
    int* y;
    x = (int*)malloc(sizeof(int));
    y = (int*)malloc(sizeof(int));
    if (random_arrow(GS, x, y, n_amazon))
    {
        GS->board[*x][*y].occupation = MISSILE;
    }
    else
    {
        printf("The amazon cannot shoot an arrow.\n");
    }
}

void shoot_spear(game_state* GS, int n_amazon)
{
    int* x;
    int* y;
    x = (int*)malloc(sizeof(int));
    y = (int*)malloc(sizeof(int));
    if (random_arrow(GS, x, y, n_amazon))
    {
        GS->board[*x][*y].occupation = MISSILE;
    }
    else
    {
        printf("The amazon cannot shoot a spear.\n");
    }
}

int move_amazon(game_state* GS)
{
    int* x, * y;
    int* n_amazon;
    x = (int*)malloc(sizeof(int));
    y = (int*)malloc(sizeof(int));
    n_amazon = (int*)malloc(sizeof(int));
    if (choose_amazon(GS, x, y, n_amazon))
    {
        GS->board[GS->positions[*n_amazon].x][GS->positions[*n_amazon].y].occupation = FREE;
        GS->board[*x][*y].occupation = find_ID(GS);
        GS->positions[*n_amazon].x = *x;
        GS->positions[*n_amazon].y = *y;
        get_treasure(GS, *x, *y);
        int art = GS->board[*x][*y].artifact;
        GS->board[*x][*y].artifact = FREE;

        switch (art)
        {
            /* no artifact */
        case 0:
            shoot_arrow(GS, *n_amazon);
            break;
            /* horse*/
        case 1:
            shoot_arrow(GS, *n_amazon);
            move_after_horse(GS, *n_amazon);
            break;
            /* broken arrow */
        case 2:
            break;
            /* spear */
        case 3:
            shoot_arrow(GS, *n_amazon);
            break;
        default:
            printf("Unknown artifact");
            break;
        }
        return 1;
    }
    else
        return 0;
}

int move_after_horse(game_state* GS, int n_amazon)
{
    int* x, * y;
    x = (int*)malloc(sizeof(int));
    y = (int*)malloc(sizeof(int));
    if (choose_after_horse(GS, x, y, n_amazon))
    {
        GS->board[GS->positions[n_amazon].x][GS->positions[n_amazon].y].occupation = FREE;
        GS->board[*x][*y].occupation = find_ID(GS);
        GS->positions[n_amazon].x = *x;
        GS->positions[n_amazon].y = *y;
        get_treasure(GS, *x, *y);
        int art = GS->board[*x][*y].artifact;
        GS->board[*x][*y].artifact = FREE;

        switch (art)
        {
            /* no artifact */
        case 0:
            shoot_arrow(GS, n_amazon);
            break;
            /* horse*/
        case 1:
            shoot_arrow(GS, n_amazon);
            move_after_horse(GS, n_amazon);
            break;
            /* broken arrow */
        case 2:
            break;
            /* spear */
        case 3:
            shoot_arrow(GS, n_amazon);
            break;
        default:
            printf("Unknown artifact");
            break;
        }
        return 1;
    }
    else
    {
        printf("This amazon cannot make a move");
        return 1;
    }
}

void add_player_data_file(FILE* fp, struct game_state* GS) {
    int i;

    for (i = 0; i < GS->fixed.number_of_players; i++) {
        fprintf(fp, "%s ", GS->player_list[i].name);
        fprintf(fp, "%d ", GS->player_list[i].ID);
        fprintf(fp, "%d\n", GS->player_list[i].points);


    }
}

void add_size_file(FILE* fp, struct game_state* GS) {
    fprintf(fp, "%d %d\n", GS->fixed.height, GS->fixed.width);
}

void add_tiles_file(FILE* fp, struct game_state* GS) {
    int i, j;

    for (i = 0; i < GS->fixed.height; i++) {
        for (j = 0; j < GS->fixed.width; j++) {
            if (j == (GS->fixed.width - 1)) {
                fprintf(fp, "%d%d%d\n", GS->board[i][j].treasure, GS->board[i][j].artifact, GS->board[i][j].occupation);
            }
            else {
                fprintf(fp, "%d%d%d ", GS->board[i][j].treasure, GS->board[i][j].artifact, GS->board[i][j].occupation);
            }
        }
    }
}

void save_data_file(char* file_name, struct game_state* GS) {

    FILE* fp = fopen(file_name, "w");

    if (fp == NULL) {
        printf("Error in saving file!");
    }
    else {
        //Printing size

        add_size_file(fp, GS);

        //Printing tiles

        add_tiles_file(fp, GS);

        //Printing player data

        add_player_data_file(fp, GS);

        fclose(fp);
    }
}

void free_memory(game_state* GS)
{
    int p = 0;
    //Freeing the memory
    while (p < GS->fixed.height) {
        free(*(GS->board + p));
        p++;
    }
    free(GS->board);
    free(GS->player_list);
    free(GS->positions);
    free(GS);
}

void test(int expected, int actual, const char* testName) {

    if (expected == actual) {
        printf("Test %s PASSED\n", testName);
    }
    else {
        printf("Test %s FAILED expected: %d actual: %d\n", testName, expected, actual);
    }

}

int cmp_coordinates(struct coordinate C1, struct coordinate C2) {

    if ((C1.x == C2.x) && (C1.y == C2.y)) {
        return 1;
    }
    else {
        return 0;
    }
}

int ac_used_horses(struct game_state* GS, struct game_state* TEST) {

    int count_horse_AC = 0, count_horse_now = 0;

    int i, j;

    for (i = 0; i < GS->fixed.height; i++) {
        for (j = 0; j < GS->fixed.width; j++) {
            if (GS->board[i][j].artifact == HORSE) {
                count_horse_now++;
            }
        }
    }

    for (i = 0; i < TEST->fixed.height; i++) {
        for (j = 0; j < TEST->fixed.width; j++) {
            if (TEST->board[i][j].artifact == HORSE) {
                count_horse_AC++;
            }
        }
    }

    return count_horse_AC - count_horse_now;
}

int ac_used_broken_arrows(struct game_state* GS, struct game_state* TEST) {

    int count_broken_arrow_AC = 0, count_broken_arrow_now = 0;

    int i, j;

    for (i = 0; i < GS->fixed.height; i++) {
        for (j = 0; j < GS->fixed.width; j++) {
            if (GS->board[i][j].artifact == BROKEN_ARROW) {
                count_broken_arrow_now++;
            }
        }
    }

    for (i = 0; i < TEST->fixed.height; i++) {
        for (j = 0; j < TEST->fixed.width; j++) {
            if (TEST->board[i][j].artifact == BROKEN_ARROW) {
                count_broken_arrow_AC++;
            }
        }
    }

    return count_broken_arrow_AC - count_broken_arrow_now;
}

void ac_points_check(struct game_state* GS, struct game_state* TEST, int used_horse) {

    int max_points_turn = 5 + used_horse * 5;
    int difference;
    int i;

    for (i = 0; i < GS->fixed.number_of_players; i++) {
        difference =  GS->player_list[i].points - TEST->player_list[i].points;

        if (difference < 0) {
            printf("Player %s lost points this turn!", GS->player_list[i].name);
        }
        else if (difference > max_points_turn) {
            printf("Players %s achieved this turn more points than it is possible!", GS->player_list[i].name);
        }
    }

}

void ac_arrow_check(struct game_state* GS, struct game_state* TEST, int used_horse, int used_broken_arrow) {

    int count_arrows_now = 0, count_arrows_AC = 0;
    int shoot_arrows = 0;
    int i, j;

    for (i = 0; i < GS->fixed.height; i++) {
        for (j = 0; j < GS->fixed.width; j++) {
            if (GS->board[i][j].occupation == MISSILE) {
                count_arrows_now++;
            }
        }
    }

    for (i = 0; i < TEST->fixed.height; i++) {
        for (j = 0; j < TEST->fixed.width; j++) {
            if (TEST->board[i][j].occupation == MISSILE) {
                count_arrows_AC++;
            }
        }
    }

    shoot_arrows = count_arrows_now - count_arrows_AC;

    int possible_shots = GS->fixed.number_of_players + used_horse - used_broken_arrow;

    if (shoot_arrows != possible_shots) {
        printf("Warning! In the last turn, players shoot %d missiles when it should be %d missiles", shoot_arrows, possible_shots);
    }
}

int ac_pawn_positions(struct game_state* GS, struct game_state* TEST, struct coordinate* position_now, struct coordinate* position_AC, int i) {

    int count = 0;
    int j, k;

    //Checking location of previous pawns
    for (j = 0; j < TEST->fixed.height; j++) {
        for (k = 0; k < TEST->fixed.width; k++) {
            if ((i + 1) == TEST->board[j][k].occupation) {
                position_AC[count].x = j;
                position_AC[count++].y = k;
            }
        }
    }
    count = 0;

    //Checking location of current pawns
    for (j = 0; j < GS->fixed.height; j++) {
        for (k = 0; k < GS->fixed.width; k++) {
            if ((i + 1) == GS->board[j][k].occupation) {
                position_now[count].x = j;
                position_now[count++].y = k;
            }
        }
    }

    return count;
}

int ac_horizontal_move(struct game_state* GS, struct coordinate* position_now, struct coordinate* position_AC, int j) {

    int possible = 0;
    int k;

    //UP
    for (k = position_AC[j].x; k > 0; k--) {
        if (k == position_now[j].x && position_AC[j].y == position_now[j].y) {
            possible = 1;
        }
    }

    //Down
    for (k = position_AC[j].x; k < GS->fixed.height; k++) {
        if (k == position_now[j].x && position_AC[j].y == position_now[j].y) {
            possible = 1;
        }
    }

    return possible;
}

int ac_vertical_move(struct game_state* GS, struct coordinate* position_now, struct coordinate* position_AC, int j) {

    int possible = 0;
    int k;

    //Left
    for (k = position_AC[j].y; k > 0; k--) {
        if (position_AC[j].x == position_now[j].x && k == position_now[j].y) {
            possible = 1;
        }
    }

    //Right
    for (k = position_AC[j].y; k < GS->fixed.height; k++) {
        if (position_AC[j].x == position_now[j].x && k == position_now[j].y) {
            possible = 1;
        }
    }

    return possible;
}

int ac_diagonal_move(struct game_state* GS, struct coordinate* position_now, struct coordinate* position_AC, int j) {

    int possible = 0;
    int k, l;

    //Up-Right

    k = position_AC[j].x;
    l = position_AC[j].y;
    while ((k > 0) || (l < GS->fixed.width)) {
        if (k == position_now[j].x && l == position_now[j].y) {
            possible = 1;
        }

        k--;
        l++;
    }

    //Up-Left

    k = position_AC[j].x;
    l = position_AC[j].y;
    while ((k > 0) || (l > 0)) {
        if (k == position_now[j].x && l == position_now[j].y) {
            possible = 1;
        }

        k--;
        l--;
    }

    //Down-Right

    k = position_AC[j].x;
    l = position_AC[j].y;
    while ((k < GS->fixed.height) || (l < GS->fixed.width)) {
        if (k == position_now[j].x && l == position_now[j].y) {
            possible = 1;
        }

        k++;
        l++;
    }

    //Down-Left

    k = position_AC[j].x;
    l = position_AC[j].y;
    while ((k < GS->fixed.height) || (l > 0)) {
        if (k == position_now[j].x && l == position_now[j].y) {
            possible = 1;
        }

        k++;
        l--;
    }

    return possible;

}

void ac_check_move(struct game_state* GS, struct game_state* TEST, struct coordinate* position_now, struct coordinate* position_AC, int i, int count) {

    int possible = 0;

    int j, k, l;

    for (j = 0; j < count; j++) {
        if (!cmp_coordinates(position_AC[j], position_now[j])) {

            //Horizontally

            if (ac_horizontal_move(GS, position_now, position_AC, j)) {
                possible = 1;
            }

            //Vertically

            if (ac_vertical_move(GS, position_now, position_AC, j)) {
                possible = 1;
            }

            //Diagonally

            if (ac_diagonal_move(GS, position_now, position_AC, j)) {
                possible = 1;
            }

            if (!possible) {
                printf("Player %s made impossible move with his amazon!\n", GS->player_list[i].name);
            }
        }
    }
    count = 0;
}

void ac_system(struct game_state* GS, struct game_state* TEST) {

    //Horse difference

    int used_horse = ac_used_horses(GS, TEST);

    //Broken arrow difference

    int used_broken_arrow = ac_used_broken_arrows(GS, TEST);

    //Sprawdzanie ruchu (jeœli nie by³y u¿yte konie)

    int i, j, k;

    if (!used_horse) {

        for (i = 0; i < GS->fixed.number_of_players; i++) {

            //pawn positions (Arrays)
            coordinate* position_now;
            position_now = (coordinate*)malloc(sizeof(coordinate) *20;
            coordinate* position_AC;
            position_AC = (coordinate*)malloc(sizeof(coordinate) * 20);

            int count = ac_pawn_positions(GS, TEST, position_now, position_AC, i);

            ac_check_move(GS, TEST, position_now, position_AC, i, count);
        }
    }

    //Points check

    ac_points_check(GS, TEST, used_horse);


    //Arrow check

    ac_arrow_check(GS, TEST, used_horse, used_broken_arrow);
}


int main(int argc, char* argv[]) {

#ifdef RUN_UNIT_TEST

    //Testing of reading file - TEST.txt

    game_state u_test;
    game_state* UT = &u_test;
    UT->name = (char*)malloc(NAME_LENGTH * sizeof(char));
    UT->name = "DoubleA";

    u_test.error = 0;
    u_test.current_player = 0;
    u_test.n_player = 0;
    u_test.fixed.number_of_pawns = 0;

    read_file("TEST.txt", UT);

    test(TRUE, UT->fixed.height == 5, "Read_height");
    test(TRUE, UT->fixed.width == 6, "Read_width");
    test(TRUE, UT->board[4][0].occupation == 5, "Read_occupation");
    test(TRUE, UT->board[2][5].treasure == 3, "Read_treasure");
    test(TRUE, UT->board[0][2].artifact == 2, "Read_artifact");
    test(TRUE, UT->fixed.number_of_players == 5, "Read_number_of_players");
    test(TRUE, !strcmp("DoubleA", UT->player_list[0].name), "Read_name");
    test(TRUE, UT->player_list[4].ID == 5, "Read_ID");
    test(TRUE, UT->player_list[1].points == 38, "Read_points");
    test(TRUE, find_ID(UT) == 1, "Find_our_ID");
    test(TRUE, fmax_of8(-12, 0, 3, 4, 5, 87, 256, 19) == 256, "Find_max_of_eight");
    test(FALSE, is_occupied(UT, 2, 2), "Check_if_occupied");

    free_memory(UT);

#endif // RUN_UNIT_TEST

    //Game state
    game_state state;
    game_state* GS = &state;
    GS->name = (char*)malloc(NAME_LENGTH * sizeof(char));
    GS->name = "DoubleA";

    state.error = 0;
    state.current_player = 0;
    state.n_player = 0;
    state.fixed.number_of_pawns = 0;

    //Ac system
    game_state check;
    game_state* TEST = &check;
    TEST->name = (char*)malloc(NAME_LENGTH * sizeof(char));
    TEST->name = "DoubleA";

    check.error = 0;
    check.current_player = 0;
    check.n_player = 0;
    check.fixed.number_of_pawns = 0;

    if (argc == 5 && !strcmp(argv[1], "phase=placement")) // four parameters, placement phase
    {
        int i = 0;
        char c;
        if (argv[2][i++] == 'a' && argv[2][i++] == 'm' && argv[2][i++] == 'a' && argv[2][i++] == 'z' && argv[2][i++] == 'o' && argv[2][i++] == 'n' && argv[2][i++] == 's' && argv[2][i++] == '=')
        {
            while ((c = argv[2][i++]) != '\0')
            {
                if (!is_digit(c))
                {
                    printf("Number of amazons is supposed to be a number\n");
                    break;
                }
                else
                    state.fixed.number_of_pawns = state.fixed.number_of_pawns * 10 + (c - '0');
            }
        }

        read_file(argv[3], GS);
        if (state.error == 1) {
            return 2;
        }
        else {
            //Placing amazons
            if (place_amazons(GS))
            {
                save_data_file(argv[4], GS);
                free_memory(GS);
                free_memory(TEST);
                return 0;
            }
            else
            {
                printf("Amazon cannot be placed on the board\n");
                return 1;
            }
        }
    }

    // three parameters, movement phase
    else if (argc == 4 && !strcmp(argv[1], "phase=movement"))
    {
        //inputfile_name = argv[2];
        //outputfile_name = argv[3];

        read_file(argv[2], GS);
        read_file("AC.txt", TEST);

        if (state.error == 1) {
            return 2;
        }
        else {
            
            //AC SYSTEM
            if (!TEST->error) {
                ac_system(GS, TEST);
            }
            
            if (move_amazon(GS))
            {
                save_data_file(argv[3], GS);
                free_memory(GS);
                free_memory(TEST);
                return 0;
            }
            else
            {
                printf("All amazons are blocked\n");
                free_memory(GS);
                free_memory(TEST);
                return 1;
            }
        }
    }

    // one parameter, displaying the name
    else if (argc == 2 && !strcmp(argv[1], "name"))
    {
        printf("Name of the player: %s", GS->name);
        free_memory(GS);
        free_memory(TEST);
    }

    else
    {
        printf("Not defined command line parameters\n");
        return 2;
    }
}
