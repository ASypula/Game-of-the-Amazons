#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FREE 0
#define OCCUPIED 1
#define MISSILE 9
#define MAX_NUMBER_OF_PLAYERS 8
#define NAME_LENGTH 15


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

void draw_board(tile** board, int row, int column) {
    int i, j;
    for (i = 0; i <= row; i++) {
        //Drawing a first row which describes columns
        if (i == 0) {
            for (j = 0; j <= column; j++) {
                if (j == 0) {
                    printf("R|C ");
                }
                else
                {
                    if (j > 10) {
                        printf(" %d ", j - 1);
                    }
                    else if (j > 100) {
                        printf(" %d ", j - 1);
                    }
                    else {
                        printf(" %d  ", j - 1);
                    }
                }
            }
        }
        //Drawing next rows
        else {
            for (j = 0; j <= column; j++) {
                //Drawing a first cell which descrbies a row
                if (j == 0) {
                    if (i > 10) {
                        printf(" %d ", i - 1);
                    }
                    else if (i > 100) {
                        printf("%d ", i - 1);
                    }
                    else {
                        printf(" %d  ", i - 1);
                    }
                }
                //Drawing a given tile
                else
                {
                    printf("%d%d%d ", board[i - 1][j - 1].treasure, board[i - 1][j - 1].artifact, board[i - 1][j - 1].occupation);
                }
            }
        }
        printf("\n");
    }

}

//Randomizing contents of each tile
tile generate_tile() {
    tile x;
    x.treasure = rand() % 6;
    x.artifact = rand() % 4;
    x.occupation = 0;
    return x;
}

void generate_board(tile** board, int* m, int* n) {
    int i, j;
    for (i = 0; i < *m; i++) {
        for (j = 0; j < *n; j++) {
            board[i][j] = generate_tile();
        }
    }
}

int get_number_of_players() {
    printf("Enter the number of players: \n");
    scanf("%d", &number_of_players);
    while (number_of_players > 8) {
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
    int chosen_row, chosen_column, i, current_player;
    for (i = 0; i < number_of_pawns; i++) {
        for (current_player = 0; current_player < number_of_players; current_player++) {

            do {
                printf("%s please, place your amazon on the board\n", player[current_player].name);
                printf("choose row: \n");
                scanf("%d", &chosen_row);
                printf("choose column: \n");
                scanf("%d", &chosen_column);
            } while (board[chosen_row][chosen_column].occupation != FREE);


            board[chosen_row][chosen_column].treasure = FREE;
            board[chosen_row][chosen_column].artifact = FREE;
            board[chosen_row][chosen_column].occupation = current_player + 1;

            draw_board(board, rows, columns);
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

/* function that gets next char after whitespaces */
int get_next(int* c) {
    *c = getchar();
    while (*c == ' ' || *c == '\t' || *c == '\n' || *c == EOF)
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
    if (board[x][y + q].occupation == OCCUPIED && board[x + p][y].occupation == OCCUPIED && board[x + p][y + q].occupation == OCCUPIED)
        return 1;
    else
        return 0;
}

/* checks if the amazon positioned on the vertical edge has any valid moves
    p = +1 if the amazon is on the left, p = -1 if the amazon is on the right of the board*/
int check_xs(tile** board, int x, int y, int p)
{
    if (board[x][y + 1].occupation == OCCUPIED && board[x][y - 1].occupation == OCCUPIED && board[x + p][y].occupation == OCCUPIED
        && board[x + p][y + 1].occupation == OCCUPIED && board[x + p][y - 1].occupation == OCCUPIED)
        return 1;
    else
        return 0;
}

/* checks if the amazon positioned on the horizontal edge has any valid moves
    p = +1 if the amazon is at the bottom, p = -1 if the amazon is at the top of the board*/
int check_ys(tile** board, int x, int y, int p)
{
    if (board[x - 1][y].occupation == OCCUPIED && board[x + 1][y].occupation == OCCUPIED && board[x][y + p].occupation == OCCUPIED
        && board[x + 1][y + p].occupation == OCCUPIED && board[x - 1][y + p].occupation == OCCUPIED)
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
    else if (x == 0 && y == (m-1))
    {
        return check_corner(board, x, y, 1, -1);
    }
    else if (x == (n-1) && y == 0)
    {
        return check_corner(board, x, y, -1, 1);
    }
    else if (x == (n-1) && y == (m-1))
    {
        return check_corner(board, x, y, -1, -1);
    }
    else if (x == 0)
    {
        return check_xs(board, x, y, 1);
    }
    else if (x == (n-1))
    {
        return check_xs(board, x, y, -1);
    }
    else if (y == 0)
    {
        return check_ys(board, x, y, 1);
    }
    else if (y == (m-1))
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
    printf("%s, please choose a tile with your amazon (row and column): ", player[current_player].name);
    get_move(x, y, c, m, n);
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
    else if (x1 > x2 && y1 < y2)
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
    printf("Choose a tile to shoot an arrow:");
    get_move(x2, y2, c, m, n);
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
    printf("Choose a tile to shoot a spear:");
    get_move(x2, y2, c, m, n);
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
    printf("Choose a tile to move the amazon: ");
    get_move(x2, y2, c, m, n);

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
        draw_board(board, m, n);
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
    srand(time(NULL));
    printf("Please, give the size of the board\n");
    printf("height: ");
    scanf("%d", &m);
    printf("width: ");
    scanf("%d", &n);


    board = malloc(m * sizeof(**board));
    int p = 0;
    while (p < m)
    {
        *(board + p) = malloc(n * sizeof(**board));
        p++;
    }
    // get_board (board, c, m, n);

    generate_board(board, rows, columns);

    draw_board(board, m, n);


    int current_player = 0;
    number_of_players = get_number_of_players();
    player_data player[MAX_NUMBER_OF_PLAYERS];
    get_players_names(number_of_players, player);
    number_of_pawns = get_number_of_pawns();
    place_amazons(number_of_players, player, board, number_of_pawns, m, n);


    int x1, x2, y1, y2;
    int* px1 = &x1;
    int* px2 = &x2;
    int* py1 = &y1;
    int* py2 = &y2;
    int q = 0;
    while (q < number_of_players)
    {
        move_amazon(board, px1, px2, py1, py2, c, player, q, m, n);
        q++;

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
