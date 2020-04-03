#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

//Makes the text White
void White_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}

//Makes the text intense yellow
void Yellow_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

//Makes the text Green
void Green_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
}

//Makes the text intense green
void Green_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

//Makes the text Blue
void Blue_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
}

//Makes the text intense Blue
void Blue_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

//Makes the text Magenta
void Magenta_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED);
}

//Makes the text intense Magenta
void Magenta_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

//Makes the text Red
void Red_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_RED);
}

//Makes the text intense Red
void Red_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
}

//Makes the text intense Cyan
void Cyan_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

//Makes the tile all whtie which means it is occupated by arrow/spear
void Occupied_tile_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}

//Function to check color for specific player ID (Sends Error message when ID is not valid (is not in range from 0-9))
void Players_color(tile **board,int i, int j) {
    switch (board[i - 1][j - 1].occupation)
    {
    case 0:
        White_txt();
        break;
    case 1:
        Green_txt();
        break;
    case 2:
        Blue_txt();
        break;
    case 3:
        Magenta_txt();
        break;
    case 4:
        Red_txt();
        break;
    case 5:
        Cyan_I_txt();
        break;
    case 6:
        Blue_I_txt();
        break;
    case 7:
        Red_I_txt();
        break;
    case 8:
        Magenta_I_txt();
        break;
    case 9:
        Occupied_tile_txt();
        break;
    default:
        Red_I_txt();
        printf("Error: Tile [%d][%d] containing ID is not containg valid number!", i - 1, j - 1);
    }
}

//structure describing tile
typedef struct tile {
    int treasure;
    int artifact;
    int occupation;
}tile;

//Function drawing given board with colors
void draw_board_color(tile **board, int *row, int *column) {
    int i, j;
    for (i = 0; i <= row; i++) {
        //Drawing a first row which describes columns: R|C␣␣1␣␣2 .....
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
        //Drawing next rows: 1␣␣045␣413␣...
        else {
            for (j = 0; j <= column; j++) {
                //Drawing a first cell which descrbies a row e.g. :␣1␣
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
                //Drawing a given tile e.g.: 025␣
                else
                {
                    //Drawing Treasure Tile with Intense Yellow color

                    Yellow_I_txt();
                    printf("%d", board[i - 1][j - 1].treasure);

                    //Drawing Artifact Tile with Intense Green Color

                    Green_I_txt();
                    printf("%d", board[i - 1][j - 1].artifact);

                    //Drawing Player ID Tile with specific to their ID color

                    Players_color(board, i, j);
                    printf("%d", board[i - 1][j - 1].occupation);

                    //Drawing Blank space

                    White_txt();
                    printf(" ");

                    //How the Tile is supposed to look e.g. : 408
                    
                    /*Printing tile without colors:
                    printf("%d%d%d ", board[i-1][j-1].treasure, board[i - 1][j - 1].artifact, board[i - 1][j - 1].occupation)*/
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

    tile **board;

    draw_board_color(board, rows, columns);

    return 0;
}
