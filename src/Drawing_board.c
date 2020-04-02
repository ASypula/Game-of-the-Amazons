#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* structure describing one tile */
typedef struct tile {
    int treasure;
    int artifact;
    int occupation;
}tile;

void draw_board(tile **board, int *row, int *column) {
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
            for (j = 0; j <= column; j++) {
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


int main()
{
    int m=10, n=10;
    int* rows = &m;
    int* columns = &n;

    tile** board;

    draw_board(board, rows, columns);

    return 0;
}
