#include "Movement.h"


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

int choose_amazon(game_state* GS, int *x, int *y, int *n_amazon)
{
    find_amazons(GS);
    int left_amazons = GS->already_placed_amazons - 1; //number of amazons that are left to be checked - 1
    int max_points = -1;
    int max_part;
    int *x1, *y1;
    x1 = (int*) malloc (sizeof(int));
    y1 = (int*) malloc (sizeof(int));
    while (left_amazons >= 0)
    {
        if (max_points < (max_part = max_points_tile (GS, x1, y1, left_amazons)))
        {
            max_points = max_part;
            *x = *x1;
            *y = *y1;
            *n_amazon = left_amazons;
        }
        left_amazons--;
    }
    if (max_points == -1) //all amazons are blocked
        {
            printf ("All amazons are blocked.\n");
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

int max_points_line (game_state* GS, int p, int q, int *dx, int *dy, int n_amazon)
{
    int points = 0;
    int x = GS->positions[n_amazon].x;
    int y = GS->positions[n_amazon].y;
    x+=p;
    y+=q;
    while ( point_in_board (GS, x, y) && !is_occupied(GS, x, y))
    {
        if (GS->board[x][y].treasure > points)
        {
            points = GS->board[x][y].treasure;
            *dx = x;
            *dy = y;
        }
        x+=p;
        y+=q;
    }
    if  ((x - p) == GS->point_1.x)
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

int tile_with_enemy (game_state* GS, int x, int y)
{
    int id = find_ID(GS);
    if (GS->board[x][y].occupation != id || GS->board[x][y].occupation != FREE || GS->board[x][y].occupation != MISSILE) // ID's of other players
        return 1;
    else
        return 0;
}

int line_with_enemy (game_state* GS, int p, int q, int *dx, int *dy, int n_amazon)
{
    int x = GS->positions[n_amazon].x;
    int y = GS->positions[n_amazon].y;
    x+=p;
    y+=q;
    while ( point_in_board (GS, x, y) && !is_occupied(GS, x, y))
    {
        x+=p;
        y+=q;
    }
    if (tile_with_enemy(GS, x, y))
    {
        *dx = x;
        *dy = y;
        return 1;
    }
    else
        return 0;
}
//to improve
int tile_with_closest_enemy (game_state* GS, int *x, int *y, int n_amazon)
{
    if (line_with_enemy(GS, -1, 0, x, y, n_amazon)) //left line
        return 1;
    else if (line_with_enemy(GS, -1, -1, x, y, n_amazon)) //left-up line
            return 1;
    else if (line_with_enemy(GS, 0, -1, x, y, n_amazon)) //up line
            return 1;
    else if (line_with_enemy(GS, 1, -1, x, y, n_amazon)) //right-up line
            return 1;
    else if (line_with_enemy(GS, 1, 0, x, y, n_amazon)) //right line
            return 1;
    else if (line_with_enemy(GS, 1, 1, x, y, n_amazon)) //right-down line
            return 1;
    else if (line_with_enemy(GS, 0, 1, x, y, n_amazon)) //down line
            return 1;
    else if (line_with_enemy(GS, -1, 1, x, y, n_amazon)) //left-down line
            return 1;
    else
        return 0;
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
    if (x == (GS->positions[n_amazon].x+p))
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
    if (valid_path_for_arrow(GS, -1, 0, x, y, n_amazon))      //left
        return 1;
    else if (valid_path_for_arrow(GS, 0, -1, x, y, n_amazon)) //up
        return 1;
    else if (valid_path_for_arrow(GS, 1, 0, x, y, n_amazon))  //right
        return 1;
    else if (valid_path_for_arrow(GS, 0, 1, x, y, n_amazon))  //down
        return 1;
    else
        return 0;
}


void shoot_arrow(game_state* GS, int *n_amazon)
{

    int *x;
    int *y;
    x = (int*) malloc (sizeof(int));
    y = (int*) malloc (sizeof(int));
    /*if (tile_with_closest_enemy (GS, x, y, *n_amazon))
    {
        GS->board[*x][*y].occupation = MISSILE;
    }
    else
    {
    */
        if (random_arrow(GS, x, y, *n_amazon))
        {
            GS->board[*x][*y].occupation = MISSILE;
        }
        else
            printf ("The amazon cannot shoot an arrow.\n");

}

void shoot_spear(game_state* GS, int *n_amazon)
{
    int *x;
    int *y;
    /*if (tile_with_closest_enemy (GS, x, y, n_amazon))
    {
        GS->board[*x][*y].occupation = MISSILE;
    }
    else*/
    if (random_arrow(GS, x, y, *n_amazon))
    {
        GS->board[*x][*y].occupation = MISSILE;
    }
    else
        printf ("The amazon cannot shoot a spear.\n");
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

        switch (GS->board[*x][*y].artifact)
        {
            /* no artifact */
            case 0:
                shoot_arrow(GS, n_amazon);
                break;
            /* horse*/
            case 1:
                shoot_arrow(GS, n_amazon);
                move_amazon(GS);
                break;
            /* broken arrow */
            case 2:
                break;
            /* spear */
            case 3:
                shoot_spear(GS, n_amazon);
                break;
            default:
                printf("Unknown artifact");
                break;
        }
        GS->board[*x][*y].artifact = FREE;
        return 1;
    }
    else
        return 0;
}
