#include "Common.h"

void blank_table(int table[], int size)
{
    int i = size - 1;
    for (i; i >= 0; i--)
    {
        table[i] = 0;
    }
}

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