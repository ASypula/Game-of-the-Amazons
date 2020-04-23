#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>


#define FREE 0
#define OCCUPIED 1
#define MISSILE 9
#define MAX_NUMBER_OF_PLAYERS 8
#define NAME_LENGTH 15
#define Empty 0
#define Horse 1
#define Broken_arrow 2
#define Spear 3
#define Missile 9
#define Normal_move 1
#define Ctrl_move 5
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

int number_of_players;
int number_of_pawns;

//Makes the text White
void White_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}

//Makes the Bold white text
void White_bold_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

//Makes the text intense yellow
void Yellow_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

//Makes the text Green
void Green_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
}

//Makes the text intense green
void Green_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

//Makes the text Blue
void Blue_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
}

//Makes the text intense Blue
void Blue_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

//Makes the text Magenta
void Magenta_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED);
}

//Makes the text intense Magenta
void Magenta_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

//Makes the text Red
void Red_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_RED);
}

//Makes the text intense Red
void Red_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
}

//Makes the text intense Cyan
void Cyan_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

//Makes the tile all whtie which means it is occupated by arrow/spear
void Occupied_tile_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}

//Function to check color for specific player ID (Sends Error message when ID is not valid (is not in range from 0-9))
void Players_color(struct tile** board, int i, int j) {
    switch (board[i - 1][j - 1].occupation)
    {
    case 0:
        White_txt();
        break;
    case 1:
        Green_txt();
        break;
    case 2:
        Blue_txt();
        break;
    case 3:
        Magenta_txt();
        break;
    case 4:
        Red_txt();
        break;
    case 5:
        Cyan_I_txt();
        break;
    case 6:
        Blue_I_txt();
        break;
    case 7:
        Red_I_txt();
        break;
    case 8:
        Magenta_I_txt();
        break;
    case 9:
        Occupied_tile_txt();
        break;
    default:
        Red_I_txt();
        printf("Error: Tile [%d][%d] containing ID is not containg valid number!", i - 1, j - 1);
    }
}

//Filling a board with content
void generate_board(struct tile** board, int* m, int* n) {
    int i, j, chance_t, chance_a;
    for (i = 0; i < *m; i++) {
        for (j = 0; j < *n; j++) {
            chance_t = rand() % 2;
            if (chance_t == 1) {
                board[i][j].treasure = (rand() % 5) + 1;
            }
            else {
                board[i][j].treasure = 0;
            }
            chance_a = rand() % 5;
            if (chance_a == 4) {
                board[i][j].artifact = (rand() % 3) + 1;
            }
            else
            {
                board[i][j].artifact = 0;
            }
            board[i][j].occupation = 0;
        }
    }
}

//Function drawing given board with colors
void draw_board_color(struct tile** board, int* row, int* column) {
    int i, j;
    for (i = 0; i <= *row; i++) {
        //Drawing a first row which describes columns
        if (i == 0) {
            for (j = 0; j <= *column; j++) {
                // R|C digit tile
                if (j == 0) {
                    printf("Row|Col  ");
                }
                // 2 digit tile
                else if (j > 10)
                {
                    printf("( %d)   ", j - 1);
                    // 3 digit tile
                }
                else if (j > 100)
                    printf("(%d)   ", j - 1);
                // 1 digit tile
                else {
                    printf("( %d )   ", j - 1);
                }
            }
        }
        //Drawing next rows: 1␣␣045␣413␣...
        else {
            for (j = 0; j <= *column; j++) {
                //Drawing a first cell which descrbies a row e.g. : ( 1 )
                if (j == 0) {
                    if (i > 10) {
                        printf(" ( %d)  ", i - 1);
                    }
                    else if (i > 100) {
                        printf(" (%d)  ", i - 1);
                    }
                    else {
                        printf(" ( %d )  ", i - 1);
                    }
                }
                //Drawing a given tile e.g.: [Horse]
                else {
                    //Program first checks if tile is not empty (Occupied with a pawn) and draws it
                    if (board[i - 1][j - 1].occupation != Empty) {
                        if (board[i - 1][j - 1].occupation != Missile) {

                            printf("[");
                            Players_color(board, i, j);
                            printf("Amaz%d", board[i - 1][j - 1].occupation);
                            White_txt();
                            printf("] ");
                        }
                        else {

                            printf("[");
                            Occupied_tile_txt();
                            printf("*****");
                            White_txt();
                            printf("] ");
                        }
                    }
                    //Program draws empty tile
                    else {
                        //Got two elements
                        if (board[i - 1][j - 1].treasure != 0 && board[i - 1][j - 1].artifact != 0) {
                            printf("[");
                            Yellow_I_txt();
                            printf("%dC", board[i - 1][j - 1].treasure);
                            Green_I_txt();
                            switch (board[i - 1][j - 1].artifact)
                            {
                            case Horse:
                                printf(" Hr");
                                break;
                            case Broken_arrow:
                                printf(" BA");
                                break;
                            case Spear:
                                printf(" Sp");
                                break;
                            }
                            White_txt();
                            printf("] ");
                        }
                        //Got no elements
                        else if (board[i - 1][j - 1].treasure == 0 && board[i - 1][j - 1].artifact == 0) {
                            printf("[");
                            printf("_____");
                            printf("] ");
                        }
                        //Got one element
                        else {
                            if (board[i - 1][j - 1].treasure != 0) {
                                printf("[");
                                Yellow_I_txt();
                                printf("%dcoin", board[i - 1][j - 1].treasure);
                                White_txt();
                                printf("] ");
                            }
                            else {
                                printf("[");
                                Green_I_txt();
                                switch (board[i - 1][j - 1].artifact)
                                {
                                case Horse:
                                    printf("Horse");
                                    break;
                                case Broken_arrow:
                                    printf("B.Arr");
                                    break;
                                case Spear:
                                    printf("Spear");
                                    break;
                                }
                                White_txt();
                                printf("] ");
                            }
                        }
                    }
                }
            }
        }
        printf("\n");
    }

}

//Reads the symbols from keybord (One and two byte ones) and changes the position of a move
void choose_tile(int* x, int* y) {
    int sign;
    int* symbol = &sign;
    *symbol = _getch();
    while (_kbhit())
    {
        *symbol = _getch();
    }

    switch (*symbol)
    {
        //LEFT
    case 75:
        if (*y == 0) {
            Red_I_txt();
            printf("You can't move on negitve tile!\n");
            White_txt();
        }
        else {
            *y -= Normal_move;
        }
        break;
        //CTRL + LEFT
    case 115:
        if (*y - Ctrl_move < 0) {
            Red_I_txt();
            printf("You can't move on negitve tile!\n");
            White_txt();
        }
        else {
            *y -= Ctrl_move;
        }
        break;
        //RIGHT
    case 77:
        *y += Normal_move;
        break;
        //CTRL + RIGHT
    case 116:
        *y += Ctrl_move;
        break;
        //DOWN
    case 80:
        *x += Normal_move;
        break;
        //CTRL + DOWN
    case 145:
        *x += Ctrl_move;
        break;
        //UP
    case 72:
        if (*x == 0) {
            Red_I_txt();
            printf("You can't move on negitve tile!\n");
            White_txt();
        }
        else {
            *x -= Normal_move;
        }
        break;
        //CTRL + UP
    case 141:
        if (*x - Ctrl_move < 0) {
            Red_I_txt();
            printf("You can't move on negitve tile!\n");
            White_txt();
        }
        else {
            *x -= Ctrl_move;
        }
        break;

        //Error message
    default:
        Red_I_txt();
        printf("Use arrow keys to change tile!\n");
        White_txt();
        break;
    }


}

void get_move_with_arrowkey(struct tile** board, int* x, int* y, int* row, int* column) {
    int symbol;

    printf("To choose tile use arrowkeys\n");

    do {

        draw_board_color(board, row, column);

        choose_tile(x, y);

        //printf("Selected tile: [%d] [%d]\n", *x, *y);
        printf("Selected tile: [");
        White_bold_txt();
        printf("%d", *x);
        White_txt();
        printf("] [");
        White_bold_txt();
        printf("%d", *y);
        White_txt();
        printf("] \n");

        printf("To confirm, press enter.\n");
        printf("To move by 5 tiles use a combination of ctrl and arrow!");

        symbol = _getch();

        system("cls");

    } while (symbol != 13); // Ends with ENTER symbol

}

int get_number_of_players() {

    printf("Enter the number of players: \n");
    scanf("%d", &number_of_players);
    while (number_of_players > MAX_NUMBER_OF_PLAYERS) {
        printf("The number of players should be less than 8\n");
        printf("Enter the number of players: \n");
        scanf("%d", &number_of_players);
    }
    return number_of_players;
}

void get_players_names(int number_of_players, player_data* player) {
    int i;
    for (i = 0; i < number_of_players; i++) {
        printf("player %d. Enter your name: \n", i + 1);
        scanf("%s", player[i].name);
        player[i].ID = i + 1;
        player[i].points = 0;
    }

}

void place_amazons(int number_of_players, player_data* player, tile** board, int number_of_pawns, int rows, int columns) // uwaga: uzytkownik moze podac nieistniejacy kafelek
{
    int chosen_row=0, chosen_column=0, i, current_player;
    for (i = 0; i < number_of_pawns; i++) {
        for (current_player = 0; current_player < number_of_players; current_player++) {

            do {
                printf("%s please, place your amazon on the board\n", player[current_player].name);

                get_move_with_arrowkey(board, &chosen_row, &chosen_column, &rows, &columns);

            } while (board[chosen_row][chosen_column].occupation != FREE);


            board[chosen_row][chosen_column].treasure = FREE;
            board[chosen_row][chosen_column].artifact = FREE;
            board[chosen_row][chosen_column].occupation = current_player + 1;

            system("cls");
        }
    }
}

int get_number_of_pawns() {
    int number_of_pawns;
    printf("please, give the number of pawns:");
    scanf("%d", &number_of_pawns);
    return number_of_pawns;
}

/* changes a number from ASCII code to the decimal number */
int number(int x)
{
    x = x - '0';
    return x;
}

/* fills the table with 0's */
void blank_table(int table[], int size)
{
    int i = size - 1;
    for (i; i >= 0; i--)
    {
        table[i] = 0;
    }
}

//NOT!!!!!!!!!!!!!!!!!!!
/* function that gets next char after whitespaces */
int get_next(int* c) {
    *c = getchar();
    while (*c == ' ' || *c == '\t' || *c == '\n' || *c == EOF) //what about boards with more than 10? taking a tile 11, 11
    {
        if (*c == EOF)
        {
            // what then?
        }
        *c = getchar();
    }
    return *c;
}

/* gets size of the board*/
void get_size(int* rows, int* columns, int* c)
{
    int row = 0;
    int col = 0;
    while ((*c = getchar()) != ' ')
        row = row * 10 + number(*c);

    while ((*c = getchar()) != '\n')
        col = col * 10 + number(*c);
    *rows = row;
    *columns = col;
}

/* gets and saves values describing one tile */
tile get_tile(int* c)
{
    tile x;
    x.treasure = number(get_next(c));
    x.artifact = number(get_next(c));
    x.occupation = number(get_next(c));
    return x;
}

/* gets and saves the board */
void get_board(tile** y, int* c, int m, int n)
{
    int i = 0, j;
    while (i < m)
    {
        j = 0;
        while (j < n)
        {
            //if ((*c = getchar()) == '\n')
            y[i][j] = get_tile(c);
            j++;
        }
        i++;
    }
}

/* checks if the amazon positioned on the corner has any valid moves
    p = +1 if the amazon is on the left, p = -1 if the amazon is on the right of the board
    q = +1 if the amazon is at the bottom, q = -1 if the amazon is at the top of the board*/
int check_corner(tile** board, int x, int y, int p, int q)
{
    if (board[x][y + q].occupation != FREE && board[x + p][y].occupation != FREE && board[x + p][y + q].occupation != FREE)
        return 1;
    else
        return 0;
}

/* checks if the amazon positioned on the vertical edge has any valid moves
    p = +1 if the amazon is on the left, p = -1 if the amazon is on the right of the board*/
int check_xs(tile** board, int x, int y, int p)
{
    if (board[x][y + 1].occupation != FREE && board[x][y - 1].occupation != FREE && board[x + p][y].occupation != FREE
        && board[x + p][y + 1].occupation != FREE && board[x + p][y - 1].occupation != FREE)
        return 1;
    else
        return 0;
}

/* checks if the amazon positioned on the horizontal edge has any valid moves
    p = +1 if the amazon is at the bottom, p = -1 if the amazon is at the top of the board*/
int check_ys(tile** board, int x, int y, int p)
{
    if (board[x - 1][y].occupation != FREE && board[x + 1][y].occupation != FREE && board[x][y + p].occupation != FREE
        && board[x + 1][y + p].occupation != FREE && board[x - 1][y + p].occupation != FREE)
        return 1;
    else
        return 0;
}

/* returns 1 if the amazon does not have any valid move; 0 otherwise*/
int no_more_moves(tile** board, int x, int y, int m, int n)
{
    if (x == 0 && y == 0)
    {
        return check_corner(board, x, y, 1, 1);
    }
    else if (x == 0 && y == (m - 1))
    {
        return check_corner(board, x, y, 1, -1);
    }
    else if (x == (n - 1) && y == 0)
    {
        return check_corner(board, x, y, -1, 1);
    }
    else if (x == (n - 1) && y == (m - 1))
    {
        return check_corner(board, x, y, -1, -1);
    }
    else if (x == 0)
    {
        return check_xs(board, x, y, 1);
    }
    else if (x == (n - 1))
    {
        return check_xs(board, x, y, -1);
    }
    else if (y == 0)
    {
        return check_ys(board, x, y, 1);
    }
    else if (y == (m - 1))
    {
        return check_ys(board, x, y, -1);
    }
    else if (check_ys(board, x, y, 1) && check_ys(board, x, y, -1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* checks if any amazon of current player has any moves
    if the player can make any move returns 0, if the player has to end/finish the game returns 1*/
int ending_for_a_player(tile** board, player_data player[], int current_player, int pawns, int m, int n)
{
    int i = 0, j;
    int k = 0;
    while (i < m)
    {
        j = 0;
        while (j < n)
        {
            if (board[i][j].occupation == player[current_player].ID && no_more_moves(board, i, j, m, n))
                k++;
            j++;
        }
        i++;
    }
    if (k == pawns)
    {
        printf("%s none of your amazons can make a move. Your game is finished.\n", player[current_player].name);
        return 1;
    }
    else
        return 0;
}

/* saves the tile to which a player wants to move an amazon/shoot an arrow/a spear */
void get_move(int* x, int* y, int* c, int m, int n)     //uwaga na tablice o wymiarze >= 10 (trzeb pobrac 2 cyfry)
{
    *x = number(get_next(c));
    *y = number(get_next(c));
    if (*x < 0 || *x > n || *y < 0 || *y > m)
    {
        printf("There is no such tile, pick another one: \n");
        get_move(x, y, c, m, n);
    }

}

/* the player chooses his amazon */
void choose_amazon(tile** board, int* x, int* y, int* c, player_data player[], int current_player, int m, int n)
{
    printf("%s, please choose a tile with your amazon: \n", player[current_player].name);
    get_move_with_arrowkey(board, x, y, &m, &n);
    if ((board[*x][*y].occupation) != player[current_player].ID)
    {
        printf("It is not your amazon!\n");
        choose_amazon(board, x, y, c, player, current_player, m, n);
    }
    if (no_more_moves(board, *x, *y, m, n))
    {
        printf("This amazon has no more valid moves.\n");
        choose_amazon(board, x, y, c, player, current_player, m, n);
    }
}

/* swaps two elements */
void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

/* gives the treasure to the player, deletes it from the board */
void get_treasure(tile** board, int x, int y, player_data player[], int current_player)
{
    if (board[x][y].treasure != 0)
    {
        player[current_player].points += board[x][y].treasure;
        board[x][y].treasure = FREE;
    }
}

/* checks whether a tile is occupied (free) or not */
int is_occupied(tile** board, int x, int y)
{
    if (board[x][y].occupation != FREE)
        return OCCUPIED;
    else
        return FREE;
}

/* checks the orthogonal path for an amazon or an arrow
    where (x1, y) - current position and (x2, y) - final position */
int check_orthogonal_path_for_x(tile** board, int x1, int x2, int y)
{
    int occupation = FREE;
    if (x1 < x2)
    {
        x1++;
        while ((x1 <= x2) && (occupation == FREE))
        {
            occupation = is_occupied(board, x1, y);
            x1++;
        }
        return occupation;
    }
    else
    {
        x1--;
        while ((x1 >= x2) && (occupation == FREE))
        {
            occupation = is_occupied(board, x1, y);
            x1--;
        }
        return occupation;
    }
}

/* checks the orthogonal path for an amazon or an arrow
    where (x, y1) - current position and (x, y2) - final position */
int check_orthogonal_path_for_y(tile** board, int x, int y1, int y2)
{
    int occupation = FREE;
    if (y1 < y2)
    {
        y1++;
        while ((y1 <= y2) && (occupation == FREE))
        {
            occupation = is_occupied(board, x, y1);
            y1++;
        }
        return occupation;

    }
    else
    {
        y1--;
        while ((y1 >= y2) && (occupation == FREE))
        {
            occupation = is_occupied(board, x, y1);
            y1--;
        }
        return occupation;
    }
}

/* checks the diagonal path for an amazon or an arrow
    where (x1, y1) - current position and (x2, y2) - destination; first (x) position is the row number*/
int check_diagonal_path(tile** board, int x1, int x2, int y1, int y2)
{
    int occupation = FREE;
    if (x1 < x2 && y1 < y2)
    {
        x1++;
        y1++;
        while (x1 <= x2 && y1 <= y2 && (occupation == FREE))
        {
            occupation = is_occupied(board, x1, y1);
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
            occupation = is_occupied(board, x1, y1);
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
            occupation = is_occupied(board, x1, y1);
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
            occupation = is_occupied(board, x1, y1);
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

/* checks path for an amazon or an arrow
    0 = path is valid; 1 = path is not valid; -1 = it is not a move*/
int path_invalid(tile** board, int x1, int x2, int y1, int y2)
{
    int occupation = FREE;
    if (x1 != x2)
    {
        if (y1 != y2)
        {
            occupation = check_diagonal_path(board, x1, x2, y1, y2);
        }
        else
            occupation = check_orthogonal_path_for_x(board, x1, x2, y1);
    }
    else
    {
        if (y1 != y2)
            occupation = check_orthogonal_path_for_y(board, x1, y1, y2);
        else /* x1 = x2, y1 = y2 */
        {
            occupation = -1; /* error: this is not a move, the tile does not change */
            printf("Error");
        }
    }
    return occupation;
}

void shoot_arrow(tile** board, int* x1, int* x2, int* y1, int* y2, int* c, int m, int n)
{
    printf("Choose a tile to shoot an arrow:\n");
    get_move_with_arrowkey(board, x2, y2, &m, &n);
    if (path_invalid(board, *x1, *x2, *y1, *y2))
    {
        printf("The path is not valid\n");
        shoot_arrow(board, x1, x2, y1, y2, c, m, n);
    }
    else
    {
        board[*x2][*y2].occupation = MISSILE;
    }
}

void shoot_spear(tile** board, int* x1, int* x2, int* y1, int* y2, int* c, int m, int n)
{
    printf("Choose a tile to shoot a spear:\n");
    get_move_with_arrowkey(board, x2, y2, &m, &n);
    if (!((*x1 == *x2) || (*y1 == *y2)) || ((x1 == x2) && (y1 == y2))) //correct???
    {
        printf("The spear has to be shot orthogonally.\n");
        shoot_spear(board, x1, x2, y1, y2, c, m, n);
    }
    else if (is_occupied(board, *x2, *y2))
    {
        printf("The tile is occupied\n");
        shoot_spear(board, x1, x2, y1, y2, c, m, n);
    }
    else
    {
        board[*x2][*y2].occupation = MISSILE;
    }

}

void move_amazon(tile** board, int* x1, int* x2, int* y1, int* y2, int* c, player_data player[], int current_player, int m, int n)
{
    choose_amazon(board, x1, y1, c, player, current_player, m, n);
    printf("Choose a tile to move the amazon: \n");
    get_move_with_arrowkey(board, x2, y2, &m, &n);

    /* the path is not valid */
    if (path_invalid(board, *x1, *x2, *y1, *y2))
    {
        printf("This path is not valid\n");
        move_amazon(board, x1, x2, y1, y2, c, player, current_player, m, n);
    }
    /* the path is valid */
    else
    {
        board[*x1][*y1].occupation = FREE;
        *x1 = *x2;
        *y1 = *y2;
        board[*x1][*y1].occupation = player[current_player].ID;
        get_treasure(board, *x1, *y1, player, current_player);
        switch (board[*x1][*y1].artifact)
        {
            /* no artifact */
        case 0:
            shoot_arrow(board, x1, x2, y1, y2, c, m, n);
            break;
            /* horse*/
        case 1:
            shoot_arrow(board, x1, x2, y1, y2, c, m, n);
            move_amazon(board, x1, x2, y1, y2, c, player, current_player, m, n);
            break;
            /* broken arrow */
        case 2:
            break;
            /* spear */
        case 3:
            shoot_spear(board, x1, x2, y1, y2, c, m, n);
            break;
        default:
            printf("Unknown artifact");
            break;
        }
        board[*x1][*y1].artifact = FREE;
    }
    system("cls");
}

int main()
{
    /* variables containing the size */
    int m, n;
    int* rows = &m;
    int* columns = &n;
    /* variable containing newly taken char from the .txt */
    int next;
    int* c = &next;
    //get_size(rows, columns, c);

    tile** board;
    //Rand seed
    int seed;
    time_t tt;
    seed = time(&tt);
    srand(seed);

    printf("Welcome to the Amazons!\n");
    printf("Please, give the size of the board you want to play on.\n");
    printf("height: ");
    scanf("%d", &m);
    printf("width: ");
    scanf("%d", &n);

    system("cls");


    board = malloc(m * sizeof(**board));
    int p = 0;
    while (p < m)
    {
        *(board + p) = malloc(n * sizeof(**board));
        p++;
    }
    // get_board (board, c, m, n);


    //Generating and drwaing board at the beginning

    generate_board(board, rows, columns);

    //draw_board_color(board, &m, &n);


    int current_player = 0;
    number_of_players = get_number_of_players();
    player_data player[MAX_NUMBER_OF_PLAYERS];

    get_players_names(number_of_players, player);

    number_of_pawns = get_number_of_pawns();
    system("cls");
    place_amazons(number_of_players, player, board, number_of_pawns, m, n);

    int* still_in_game;
    still_in_game = (int*)malloc(number_of_players * sizeof(int));
    //int still_in_game[number_of_players];


    blank_table(still_in_game, number_of_players);



    int x1=0, x2=0, y1=0, y2=0;
    int* px1 = &x1;
    int* px2 = &x2;
    int* py1 = &y1;
    int* py2 = &y2;
    int n_player = 0;
    int with_valid_moves = number_of_players;

    while (with_valid_moves > 0)
    {
        if ((still_in_game[n_player] != FREE) || ending_for_a_player(board, player, n_player, number_of_pawns, m, n))
        {
            if (still_in_game[n_player] == FREE)
            {
                still_in_game[n_player] = OCCUPIED;
                with_valid_moves--;
            }
        }
        else
        {
            move_amazon(board, px1, px2, py1, py2, c, player, n_player, m, n);
        }
        n_player = (n_player + 1) % number_of_players;
    }

    /* freeing the memory */
    while (p < m)
    {
        free(*(board + p));
        p++;
    }
    free(board);


    return 0;
}
