#include "Movement.h"

void choose_amazon(game_state* GS, int* x, int* y)
{
    printf("%s, please choose a tile with your amazon (row and column): ", GS->player_list[GS->n_player].name);
    get_move_with_arrowkey(GS, x, y);
    if ((GS->board[*x][*y].occupation) != GS->player_list[GS->n_player].ID)
    {
        printf("It is not your amazon!\n");
        choose_amazon(GS, x, y);
    }
    if (no_more_moves(GS, *x, *y))
    {
        printf("This amazon has no more valid moves.\n");
        choose_amazon(GS, x, y);
    }
}

void get_treasure(game_state* GS)
{
    if (GS->board[GS->point_1.x][GS->point_1.y].treasure != 0)
    {
        GS->player_list[GS->n_player].points += GS->board[GS->point_1.x][GS->point_1.y].treasure;
        GS->board[GS->point_1.x][GS->point_1.y].treasure = FREE;
    }
}

void shoot_arrow(game_state* GS)
{
    printf("Choose a tile to shoot an arrow:");
    get_move_with_arrowkey(GS, &(GS->point_2.x), &(GS->point_2.y));
    if (path_invalid(GS, GS->point_1.x, GS->point_2.x, GS->point_1.y, GS->point_2.y))
    {
        printf("The path is not valid\n");
        shoot_arrow(GS);
    }
    else
    {
        GS->board[GS->point_2.x][GS->point_2.y].occupation = MISSILE;
    }
}

void shoot_spear(game_state* GS)
{
    printf("Choose a tile to shoot a spear:");
    get_move_with_arrowkey(GS, &(GS->point_2.x), &(GS->point_2.y));
    if (!((GS->point_1.x == GS->point_2.x) || (GS->point_1.y == GS->point_2.y)) || ((GS->point_1.x == GS->point_2.x) && (GS->point_1.y == GS->point_2.y))) //correct???
    {
        printf("The spear has to be shot orthogonally.\n");
        shoot_spear(GS);
    }
    else if (is_occupied(GS, GS->point_2.x, GS->point_2.y))
    {
        printf("The tile is occupied\n");
        shoot_spear(GS);
    }
    else
    {
        GS->board[GS->point_2.x][GS->point_2.y].occupation = MISSILE;
    }
}

void move_amazon(game_state* GS)
{
    choose_amazon(GS, &(GS->point_1.x), &(GS->point_1.y));
    printf("Choose a tile to move the amazon: ");
    get_move_with_arrowkey(GS, &(GS->point_2.x), &(GS->point_2.y));

    /* the path is not valid */
    if (path_invalid(GS, GS->point_1.x, GS->point_2.x, GS->point_1.y, GS->point_2.y))
    {
        printf("This path is not valid\n");
        move_amazon(GS);
    }
    /* the path is valid */
    else
    {
        GS->board[GS->point_1.x][GS->point_1.y].occupation = FREE;
        GS->point_1.x = GS->point_2.x;
        GS->point_1.y = GS->point_2.y;
        GS->board[GS->point_1.x][GS->point_1.y].occupation = GS->player_list[GS->current_player].ID;
        get_treasure(GS);
        draw_board_color(GS);
        switch (GS->board[GS->point_1.x][GS->point_1.y].artifact)
        {
            /* no artifact */
        case 0:
            shoot_arrow(GS);
            break;
            /* horse*/
        case 1:
            shoot_arrow(GS);
            move_amazon(GS);
            break;
            /* broken arrow */
        case 2:
            break;
            /* spear */
        case 3:
            shoot_spear(GS);
            break;
        default:
            printf("Unknown artifact");
            break;
        }
        GS->board[GS->point_1.x][GS->point_1.y].artifact = FREE;
    }
    system("cls");
}

int is_occupied(game_state* GS, int x, int y)
{
    if (GS->board[x][y].occupation != FREE)
        return OCCUPIED;
    else
        return FREE;
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
            occupation = -1; /* error: this is not a move, the tile does not change */
            printf("Error");
        }
    }
    return occupation;
}

int check_corner(game_state* GS, int x, int y, int p, int q)
{
    if (GS->board[x][y + q].occupation != FREE && GS->board[x + p][y].occupation != FREE && GS->board[x + p][y + q].occupation != FREE)
        return 1;
    else
        return 0;
}

int check_xs(game_state* GS, int x, int y, int p)
{
    if (GS->board[x][y + 1].occupation != FREE && GS->board[x][y - 1].occupation != FREE && GS->board[x + p][y].occupation != FREE
        && GS->board[x + p][y + 1].occupation != FREE && GS->board[x + p][y - 1].occupation != FREE)
        return 1;
    else
        return 0;
}

int check_ys(game_state* GS, int x, int y, int p)
{
    if (GS->board[x - 1][y].occupation != FREE && GS->board[x + 1][y].occupation != FREE && GS->board[x][y + p].occupation != FREE
        && GS->board[x + 1][y + p].occupation != FREE && GS->board[x - 1][y + p].occupation != FREE)
        return 1;
    else
        return 0;
}

int no_more_moves(game_state* GS, int x, int y)
{
    int m = GS->fixed.height;
    int n = GS->fixed.width;
    if (x == 0 && y == 0)
    {
        return check_corner(GS, x, y, 1, 1);
    }
    else if (x == 0 && y == (m - 1))
    {
        return check_corner(GS, x, y, 1, -1);
    }
    else if (x == (n - 1) && y == 0)
    {
        return check_corner(GS, x, y, -1, 1);
    }
    else if (x == (n - 1) && y == (m - 1))
    {
        return check_corner(GS, x, y, -1, -1);
    }
    else if (x == 0)
    {
        return check_xs(GS, x, y, 1);
    }
    else if (x == (n - 1))
    {
        return check_xs(GS, x, y, -1);
    }
    else if (y == 0)
    {
        return check_ys(GS, x, y, 1);
    }
    else if (y == (m - 1))
    {
        return check_ys(GS, x, y, -1);
    }
    else if (check_ys(GS, x, y, 1) && check_ys(GS, x, y, -1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int ending_for_a_player(game_state* GS)
{
    int i = 0, j;
    int k = 0;
    while (i < GS->fixed.height)
    {
        j = 0;
        while (j < GS->fixed.width)
        {
            if (GS->board[i][j].occupation == GS->player_list[GS->n_player].ID && no_more_moves(GS, i, j))
                k++;
            j++;
        }
        i++;
    }
    if (k == GS->fixed.number_of_pawns)
    {
        printf("%s none of your amazons can make a move. Your game is finished.\n", GS->player_list[GS->n_player].name);
        return 1;
    }
    else
        return 0;
}