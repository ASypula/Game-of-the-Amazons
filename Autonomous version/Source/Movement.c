#include "Movement.h"
#include "Input.h"
#include "Common.h"
#include "Output.h"
#include <stdlib.h>
#include <stdio.h>


int point_in_board (game_state* GS, int x, int y)
{
    if ((x >= 0) && (y >=0) && (x < GS->fixed.height) && (y < GS->fixed.width))
        return 1;
    else
        return 0;
}

int is_occupied(game_state* GS, int x, int y)
{
    if (GS->board[x][y].occupation != FREE)
        return OCCUPIED;
    else
        return FREE;
}

void find_amazons (game_state* GS)
{
    int id = find_ID(GS);
    int placed_pawns = 0;
    int i, j;
	GS->positions = (coordinate*)malloc(sizeof(coordinate));
	for (i = 0; i < GS->fixed.height; i++) {
		for (j = 0; j < GS->fixed.width; j++) {
			if (GS->board[i][j].occupation == id) {
                GS->positions = (coordinate*) realloc (GS->positions, (placed_pawns+1) * sizeof(coordinate));
                GS->positions[placed_pawns].x = i;
                GS->positions[placed_pawns].y = j;
                placed_pawns++;
            }
		}
	}
	GS->already_placed_amazons = placed_pawns;
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
    else if (x1 > x2 && y1 < y2)
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

int path_to_horse (game_state* GS, int *dx, int *dy, int n_amazon)
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
                (*dx) ++;
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


int choose_amazon(game_state* GS, int *x, int *y, int *n_amazon)
{
    find_amazons(GS);
    int left_amazons = GS->already_placed_amazons - 1; //number of amazons that are left to be checked - 1
    int max_points = -1;
    int max_part;
    int *x1, *y1;
    int is_horse = 0;
    x1 = (int*) malloc (sizeof(int));
    y1 = (int*) malloc (sizeof(int));
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
        else if (max_points < (max_part = max_points_tile (GS, x1, y1, left_amazons)))
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
            printf ("All amazons are blocked.\n");
            return 0;
        }
    else
        return 1;
}

int choose_after_horse(game_state* GS, int *x, int *y, int n_amazon)
{
    int max_points = -1;
    int max_part;
    int *x1, *y1;
    int is_horse = 0;
    x1 = (int*) malloc (sizeof(int));
    y1 = (int*) malloc (sizeof(int));
    if (path_to_horse(GS, x1, y1, n_amazon))
    {
        *x = *x1;
        *y = *y1;
        max_points = 0;
    }
    else if (max_points < (max_part = max_points_tile (GS, x1, y1, n_amazon)))
        {
            max_points = max_part;
            *x = *x1;
            *y = *y1;
        }
    if (max_points == -1) //this amazon is blocked
        {
            printf ("The amazon is blocked.\n");
            return 0;
        }
    else
        return 1;
}


void get_treasure(game_state* GS, int x, int y)
{
    if (GS->board[x][y].treasure != 0)
    {
        GS->player_list[find_ID(GS)-1].points += GS->board[x][y].treasure;
        GS->board[x][y].treasure = FREE;
    }
}

int max_points_line (game_state* GS, int p, int q, int *dx, int *dy, int n_amazon)
{
    int points = 0;
    int x = GS->positions[n_amazon].x;
    int y = GS->positions[n_amazon].y;
    x+=p;
    y+=q;
    while ( point_in_board (GS, x, y) && !is_occupied(GS, x, y))
    {
        if (GS->board[x][y].treasure >= points)
        {
            points = GS->board[x][y].treasure;
            *dx = x;
            *dy = y;
        }
        x+=p;
        y+=q;
    }
    if  ((x - p) == GS->positions[n_amazon].x && (y - q) == GS->positions[n_amazon].y)
        return -1;
    else
        return points;
}

int max_points_tile (game_state* GS, int *x, int *y, int n_amazon)
{
    int max_points;
    int left = max_points_line (GS, 0, -1, x, y, n_amazon);
    int left_up = max_points_line (GS, -1, -1, x, y, n_amazon);
    int up = max_points_line (GS, -1, 0, x, y, n_amazon);
    int right_up = max_points_line (GS, -1, 1, x, y, n_amazon);
    int right = max_points_line (GS, 0, 1, x, y, n_amazon);
    int right_down = max_points_line (GS, 1, 1, x, y, n_amazon);
    int down = max_points_line (GS, 1, 0, x, y, n_amazon);
    int left_down = max_points_line (GS, 1, -1, x, y, n_amazon);
    max_points = fmax_of8(left, left_up, up, right_up, right, right_down, down, left_down);
    if (max_points != -1)
    {
        if (max_points == left)
        {
            max_points = max_points_line (GS, 0, -1, x, y, n_amazon); //just to remember the place of the tile with max points
        }
        else if (max_points == left_up)
        {
            max_points = max_points_line (GS, -1, -1, x, y, n_amazon);
        }
        else if (max_points == up)
        {
            max_points = max_points_line (GS, -1, 0, x, y, n_amazon);
        }
        else if (max_points == right_up)
        {
            max_points = max_points_line (GS, -1, 1, x, y, n_amazon);
        }
        else if (max_points == right)
        {
            max_points = max_points_line (GS, 0, 1, x, y, n_amazon);
        }
        else if (max_points == right_down)
        {
            max_points = max_points_line (GS, 1, 1, x, y, n_amazon);
        }
        else if (max_points == down)
        {
            max_points = max_points_line (GS, 1, 0, x, y, n_amazon);
        }
        else if (max_points == left_down)
        {
            max_points = max_points_line (GS, 1, -1, x, y, n_amazon);
        }
        return max_points;
    }
    else
        return -1;
}


int valid_path_for_arrow(game_state* GS, int p, int q, int *dx, int *dy, int n_amazon)
{
    int x = GS->positions[n_amazon].x;
    int y = GS->positions[n_amazon].y;
    x+=p;
    y+=q;
    while (point_in_board(GS, x, y) && !is_occupied(GS, x, y) )
    {
        x+=p;
        y+=q;
    }
    if (x == (GS->positions[n_amazon].x+p) && y == (GS->positions[n_amazon].y+q))
        return 0;
    else
    {
        *dx = x - p;
        *dy = y - q;
        return 1;
    }
}


int random_arrow (game_state* GS, int *x, int *y, int n_amazon)
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
int random_spear (game_state* GS, int *x, int *y, int n_amazon)
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


void shoot_arrow(game_state* GS, int n_amazon)
{
    int *x;
    int *y;
    x = (int*) malloc (sizeof(int));
    y = (int*) malloc (sizeof(int));
    if (random_arrow(GS, x, y, n_amazon))
    {
        GS->board[*x][*y].occupation = MISSILE;
    }
    else
    {
        printf ("The amazon cannot shoot an arrow.\n");
    }
}

void shoot_spear(game_state* GS, int n_amazon)
{
    int *x;
    int *y;
    x = (int*) malloc (sizeof(int));
    y = (int*) malloc (sizeof(int));
    if (random_arrow(GS, x, y, n_amazon))
    {
        GS->board[*x][*y].occupation = MISSILE;
    }
    else
    {
        printf ("The amazon cannot shoot a spear.\n");
    }
}

int move_amazon(game_state* GS)
{
    int *x, *y;
    int *n_amazon;
    x = (int*) malloc (sizeof(int));
    y = (int*) malloc (sizeof(int));
    n_amazon = (int*) malloc (sizeof(int));
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
    int *x, *y;
    x = (int*) malloc (sizeof(int));
    y = (int*) malloc (sizeof(int));
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
