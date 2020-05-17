#include "Common.h"


int get_next(game_state* GS)
{
    int p = 0;
    while (GS->c != ' ')
    {
        p = 10 * p + number(GS->c);
        GS->c = getchar();
    }
    while (GS->c == ' ' || GS->c == '\t' || GS->c == '\n' || GS->c == EOF) //what about boards with more than 10? taking a tile 11, 11
    {
        if (GS->c == EOF)
        {
            // what then?
        }
        GS->c = getchar();
    }
    return p;
}

int number(int x)
{
    x = x - '0';
    return x;
}

int fmax (int x, int y)
{
    if  (x > y)
        return x;
    else
        return y;
}

int fmax_of8 (int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8)
{
    int max_x;
    max_x = fmax(fmax(fmax(x1, x2), fmax(x3, x4)), fmax(fmax(x5, x6), fmax(x7, x8)));
    return max_x;
}
