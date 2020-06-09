#include "Common.h"

int is_digit (char c)
{
    if (c >= MIN_ASCII_DIGIT && c <= MAX_ASCII_DIGIT)
        return 1;
    else
        return 0;
}

int find_ID (game_state* GS)
{
    int i = 0;
    while (strcmp(GS->player_list[i].name, GS->name))
    {
        i++;
    }
    return GS->player_list[i].ID;
}

int number(int x)
{
    x = x - '0';
    return x;
}

int find_max (int x, int y)
{
    if  (x > y)
        return x;
    else
        return y;
}

int fmax_of8 (int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8)
{
    int max_x;
    max_x = find_max(find_max(find_max(x1, x2), find_max(x3, x4)), find_max(find_max(x5, x6), find_max(x7, x8)));
    return max_x;
}

void free_memory (game_state* GS)
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

int cmp_coordinates(struct coordinate C1, struct coordinate C2){

    if((C1.x==C2.x)&&(C1.y==C2.y)){
        return 1;
    }
    else{
        return 0;
    }
}

void test(int expected, int actual, const char* testName){

    if(expected==actual){
        printf("Test %s PASSED\n", testName);
    }
    else{
        printf("Test %s FAILED expected: %d actual: %d\n", testName, expected, actual);
    }

}