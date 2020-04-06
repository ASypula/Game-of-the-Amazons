#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FREE 0
#define OCCUPIED 1
#define MISSILE 9
#define MAX_NUMBER_OF_PLAYERS 8

/* structure describing one tile */
typedef struct tile {
    int treasure;
    int artifact;
    int occupation;
}tile;

typedef struct player_data{
    char name[15];
    int ID;
    int points;
}player_data;

void placing_the_amazon(int i, int j, int current_player, tile **board){
    board[i][j].treasure = 0;
    board[i][j].artifact = 0;
    board[i][j].occupation = current_player+1;
}


/* changes a number from ASCII code to the decimal number */
int number (int x)
{
    x = x - '0';
    return x;
}

/* function that gets next char after whitespaces */
int get_next (int *c) {
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
void get_size (int *rows, int *columns, int *c)
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
tile get_tile (int *c)
{
    tile x;
    x.treasure = number (get_next(c));
    x.artifact = number(get_next(c));
    x.occupation = number(get_next(c));
    return x;
}

/* gets and saves the board */
void get_board (tile **y, int *c, int m, int n)
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

void draw_board(tile **board, int *row, int *column) {
    int i, j;
    for (i = 0; i <= *row; i++) {
        //Drawing a first row which describes columns
        if (i == 0) {
            for (j = 0; j <= *column; j++) {
                if (j == 0) {
                    printf("R|C ");
                }
                else
                {
                    if (j > 9) {
                        printf(" %d ", j);
                    }
                    else if (j > 99) {
                        printf(" %d ", j);
                    }
                    else {
                        printf(" %d  ", j);
                    }
                }
            }
        }
        //Drawing next rows
        else {
            for (j = 0; j <= *column; j++) {
                //Drawing a first cell which descrbies a row
                if (j == 0) {
                    if (i > 9) {
                        printf(" %d ", i);
                    }
                    else if (i > 99) {
                        printf("%d ", i);
                    }
                    else {
                        printf(" %d  ", i);
                    }
                }
                //Drawing a given tile
                else
                {
                    printf("%d%d%d ", board[i-1][j-1].treasure, board[i - 1][j - 1].artifact, board[i - 1][j - 1].occupation);
                }
            }
        }
        printf("\n");
    }

}


/* checks if the amazon positioned on the corner has any valid moves
    p = +1 if the amazon is on the left, p = -1 if the amazon is on the right of the board
    q = +1 if the amazon is at the bottom, q = -1 if the amazon is at the top of the board*/
int check_corner (tile ** board, int x, int y, int p, int q)
{
    if (board[x][y+q].occupation == OCCUPIED && board[x+p][y].occupation == OCCUPIED && board[x+p][y+q].occupation == OCCUPIED)
            return 1;
        else
            return 0;
}

/* checks if the amazon positioned on the vertical edge has any valid moves
    p = +1 if the amazon is on the left, p = -1 if the amazon is on the right of the board*/
int check_xs (tile **board, int x, int y, int p)
{
    if (board[x][y+1].occupation == OCCUPIED && board[x][y-1].occupation == OCCUPIED && board[x+p][y].occupation == OCCUPIED
        && board[x+p][y+1].occupation == OCCUPIED && board[x+p][y-1].occupation == OCCUPIED)
            return 1;
        else
            return 0;
}

/* checks if the amazon positioned on the horizontal edge has any valid moves
    p = +1 if the amazon is at the bottom, p = -1 if the amazon is at the top of the board*/
int check_ys (tile **board, int x, int y, int p)
{
    if (board[x-1][y].occupation == OCCUPIED && board[x+1][y].occupation == OCCUPIED && board[x][y+p].occupation == OCCUPIED
        && board[x+1][y+p].occupation == OCCUPIED && board[x-1][y+p].occupation == OCCUPIED)
            return 1;
        else
            return 0;
}

/* returns 1 if the amazon does not have any valid move; 0 otherwise*/
int no_more_moves (tile **board, int x, int y, int m, int n)  //x czy y porownywac z m i n??
{
    if (x == 1 && y == 1)
    {
        return check_corner (board, x, y, 1, 1);
    }
    else if (x == 1 && y == m)
    {
        return check_corner (board, x, y, 1, -1);
    }
    else if (x == n && y == 1)
    {
        return check_corner (board, x, y, -1, 1);
    }
    else if (x == n && y == m)
    {
        return check_corner (board, x, y, -1, -1);
    }
    else if (x == 1)
    {
        return check_xs (board, x, y, 1);
    }
    else if (x == n)
    {
        return check_xs (board, x, y, -1);
    }
    else if (y == 1)
    {
        return check_ys (board, x, y, 1);
    }
    else if (y == m)
    {
        return check_ys (board, x, y, -1);
    }
    else if (check_ys (board, x, y, 1) && check_ys (board, x, y, -1))
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

/* saves the tile to which a player wants to move an amazon/shoot an arrow/a spear */
void get_move (int *x, int *y, int *c, int m, int n)
{
    *x = number (get_next(c));
    *y = number (get_next(c));
    if (*x < 1 || *x > n || *y < 1 || *y > m)   //numerujemy od 0 czy od 1 plansze?, m i n dobrze?
    {
        printf("There is no such tile, pick another one: ");
        get_move (x, y, c, m, n);
    }

}

/* the player chooses his amazon */
void choose_amazon (tile **board, int *x, int *y, int *c, player_data player[], int current_player, int m, int n)
{
    printf ("Choose a tile with your amazon: ");
    get_move (x, y, c, m, n);
    if ((board[*x][*y].occupation) != player[current_player].ID)
    {
        printf ("It is not your amazon!");
        choose_amazon (board, x, y, c, player, current_player, m, n);
    }
    if (no_more_moves (board, *x, *y, m, n))
    {
        printf ("This amazon has no more valid moves.");
        choose_amazon (board, x, y, c, player, current_player, m, n);
    }
}

/* swaps two elements */
void swap (int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

/* gives the treasure to the player, deletes it from the board */
void get_treasure (tile **board, int x, int y, player_data player[], int current_player)
{
    if (board[x][y].treasure != 0)
    {
        player[current_player].points += board[x][y].treasure;
        board[x][y].treasure = FREE;
    }
}

/* checks whether a tile is occupied (free) or not */
int is_occupied (tile **board, int x, int y)
{
    if (board[x][y].occupation != FREE)
        return OCCUPIED;
    else
        return FREE;
}

/* checks the orthogonal path for an amazon or an arrow
    where (x1, y) - current position and (x2, y) - final position */
int check_orthogonal_path_for_x (tile **board, int x1, int x2, int y)
{
    int occupation = FREE;
    if (x1 > x2)
        swap (&x1, &x2);
    while ((x1 <= x2) && (occupation == FREE))
    {
        occupation = is_occupied (board, x1, y);
         x1++;
    }
    return occupation;
}

/* checks the orthogonal path for an amazon or an arrow
    where (x, y1) - current position and (x, y2) - final position */
int check_orthogonal_path_for_y (tile **board, int x, int y1, int y2)
{
    int occupation = FREE;
    if (y1 > y2)
        swap (&y1, &y2);
    while ((y1 <= y2) && (occupation == FREE))
    {
        occupation = is_occupied (board, x, y1);
         y1++;
    }
    return occupation;
}

/* checks the diagonal path for an amazon or an arrow
    where (x1, y1) - current position and (x2, y2) - destination*/
int check_diagonal_path (tile **board, int x1, int x2, int y1, int y2)
{
    int occupation = FREE;
    if (x1 > x2)
        swap (&x1, &x2);
    if (y1 > y2)
        swap (&y1, &y2);
    while (x1 <= x2 && y1 <= y2 && (occupation == FREE))
    {
        occupation = is_occupied (board, x1, y1);
        x1++;
        y1++;
    }
    if (((x1+1) == x2)&& ((y1+1) == y2))
        return occupation;
    else
    {
        printf ("The path is not a straight line\n");
        return OCCUPIED;

    }
}

/* checks path for an amazon or an arrow
    0 = path is valid; 1 = path is not valid; -1 = it is not a move*/
int path_invalid (tile **board, int x1, int x2, int y1, int y2)
{
    int occupation = FREE;
    if (x1 != x2)
    {
        if (y1 != y2)
            occupation = check_diagonal_path (board, x1, x2, y1, y2);
        else
            occupation = check_orthogonal_path_for_x (board, x1, x2, y1);
    }
    else
    {
        if (y1 != y2)
            occupation = check_orthogonal_path_for_y (board, x1, y1, y2);
        else /* x1 = x2, y1 = y2 */
        {
            occupation = -1; /* error: this is not a move, the tile does not change */
            printf ("Error");
        }
    }
    return occupation;
}

void shoot_arrow (tile **board, int *x1, int *x2, int *y1, int *y2, int *c, int m, int n)
{
    printf ("Choose tile to shoot an arrow:");
    get_move(x2, y2, c, m, n);
    if (path_invalid(board, *x1, *x2, *y1, *y2))
    {
        printf ("The path is not valid");
        shoot_arrow (board, x1, x2, y1, y2, c, m, n);
    }
    else
    {
        board[*x2][*y2].occupation = MISSILE;
    }
}

void shoot_spear (tile **board, int *x1, int *x2, int *y1, int *y2, int *c, int m, int n)
{
    printf ("Choose tile to shoot a spear:");
    get_move(x2, y2, c, m, n);
    if (!((*x1 == *x2) || (*y1 == *y2)) || ((x1 == x2) && (y1 == y2))) //correct???
    {
        printf ("The spear has to be shot orthogonally.");
        shoot_spear (board, x1, x2, y1, y2, c, m, n);
    }
    else if (is_occupied (board, *x2, *y2))
    {
        printf ("The tile is occupied");
        shoot_spear (board, x1, x2, y1, y2, c, m, n);
    }
    else
    {
        board[*x2][*y2].occupation = MISSILE;
    }

}



void move_amazon (tile **board, int *x1, int *x2, int *y1, int *y2, int *c, player_data player[], int current_player, int m, int n)
{
    choose_amazon (board, x1, y1, c, player, current_player, m, n);
    printf ("Choose a tile to move the amazon: ");
    get_move (x2, y2, c, m, n);

    /* the path is not valid */
    if (path_invalid(board, *x1, *x2, *y1, *y2))
    {
        printf ("This path is not valid\n");
        move_amazon(board, x1, x2, y1, y2, c, player, current_player, m, n);
    }
    /* the path is valid */
    else
    {
        board[*x1][*y1].occupation = FREE;
        *x1 = *x2;
        *y1 = *y2;
        board[*x1][*y1].occupation = player[current_player].ID;
        get_treasure (board, *x1, *y1, player, current_player);
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
                shoot_spear (board, x1, x2, y1, y2, c, m, n);
                break;
            default:
                printf ("Unknown artifact");
                break;
        }
    }
}


int main()
{
    /* variables containing the size */
    int m, n;
    int *rows = &m;
    int *columns = &n;
    /* variable containing newly taken char from the .txt */
    int next;
    int *c = &next;
    get_size(rows, columns, c);
    tile **board;
    board = malloc (m * sizeof(**board));
    int p = 0;
    while (p < m)
    {
        *(board + p) = malloc (n * sizeof (**board));
        p++;
    }
    get_board (board, c, m, n);
    draw_board(board, rows, columns);
    int number_of_players;
    do {
        printf("Enter the number of players: \n");
        scanf("%d", &number_of_players);
    } while (number_of_players > 8);

    player_data player[MAX_NUMBER_OF_PLAYERS];
    int i = 0;
    for ( i; i < number_of_players; i++) {
        printf("player %d. Enter your name: \n", i + 1);
        scanf("%s", player[i].name);
        player[i].ID = i + 1;
        player[i].points = 0;
    }
    int chosen_row, chosen_column, number_of_pawns;
    int current_player = 0;

    for (i = 0; i < number_of_pawns; i++) {
        for (current_player; current_player < number_of_players; current_player++) {

            printf("%s please, place your amazon on the board", player[current_player].name);
            do {
                scanf("%d", &chosen_row);
                scanf("%d", &chosen_column);
            } while (board[chosen_row][chosen_column].occupation != 0);

            placing_the_amazon(chosen_row, chosen_column, current_player, board);

        }
    }
    int x1, x2, y1, y2;
    int *px1 = &x1;
    int *px2 = &x2;
    int *py1 = &y1;
    int *py2 = &y2;
    move_amazon (board, px1, px2, py1, py2, c, player, current_player, m, n);
    /* freeing the memory */
    while (p < m)
    {
        free(*(board + p));
        p++;
    }
    free(board);


    return 0;
}
