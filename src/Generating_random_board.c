#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_boardfile(int* row, int* column) {

    int i, j;
    FILE* f;
    f = fopen("boardfile.txt", "w");

    fprintf(f, "%d %d\n", *row, *column);

    for (i = 0; i < *row; i++) {
        for (j = 0; j < *column; j++)
        {
            fprintf(f, "%d%d0 ", (rand() % 6), (rand() % 4));
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

int main()
{
    int row, column, i, j;
    int* pr = &row;
    int* pc = &column;
    srand(time(NULL));

    //User gives demanded size of the board (row, column)
    printf("Please, give the size of the board\n");
    printf("height: ");
    scanf("%d", &row);
    printf("width: ");
    scanf("%d", &column);

    generate_boardfile(pr, pc);

    return 0;
}
