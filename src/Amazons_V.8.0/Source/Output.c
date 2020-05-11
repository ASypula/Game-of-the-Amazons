#include "Output.h"

void White_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}

void White_bold_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void Yellow_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void Green_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
}

void Green_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void Blue_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
}

void Blue_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void Magenta_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED);
}

void Magenta_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void Red_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_RED);
}

void Red_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void Cyan_I_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void Occupied_tile_txt() {
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}

void Players_color(struct game_state* GS, int i, int j) {
    switch (GS->board[i - 1][j - 1].occupation)
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

void generate_board(struct game_state* GS) {
    int i, j, chance_t, chance_a;
    for (i = 0; i < GS->fixed.width; i++) {
        for (j = 0; j < GS->fixed.height; j++) {
            chance_t = rand() % 2;
            if (chance_t == 1) {
                GS->board[i][j].treasure = (rand() % 5) + 1;
            }
            else {
                GS->board[i][j].treasure = EMPTY;
            }
            chance_a = rand() % 5;
            if (chance_a == 4) {
                GS->board[i][j].artifact = (rand() % 3) + 1;
            }
            else
            {
                GS->board[i][j].artifact = EMPTY;
            }
            GS->board[i][j].occupation = EMPTY;
        }
    }
}

void draw_board_color(struct game_state* GS) {
    int i, j;
    for (i = 0; i <= GS->fixed.height; i++) {
        //Drawing a first row which describes columns
        if (i == 0) {
            for (j = 0; j <= GS->fixed.width; j++) {
                // R|C digit tile
                if (j == 0) {
                    printf("Row|Col  ");
                }
                // 2 digit tile
                else if (j > 10)
                {
                    printf("( %d)   ", j - 1);
                    // 3 digit tile
                }
                else if (j > 100)
                    printf("(%d)   ", j - 1);
                // 1 digit tile
                else {
                    printf("( %d )   ", j - 1);
                }
            }
        }
        //Drawing next rows: 1␣␣045␣413␣...
        else {
            for (j = 0; j <= GS->fixed.width; j++) {
                //Drawing a first cell which descrbies a row e.g. : ( 1 )
                if (j == 0) {
                    if (i > 10) {
                        printf(" ( %d)  ", i - 1);
                    }
                    else if (i > 100) {
                        printf(" (%d)  ", i - 1);
                    }
                    else {
                        printf(" ( %d )  ", i - 1);
                    }
                }
                //Drawing a given tile e.g.: [Horse]
                else {
                    //Program first checks if tile is not empty (Occupied with a pawn) and draws it
                    if (GS->board[i - 1][j - 1].occupation != EMPTY) {
                        if (GS->board[i - 1][j - 1].occupation != MISSILE) {

                            printf("[");
                            Players_color(GS, i, j);
                            printf("Amaz%d", GS->board[i - 1][j - 1].occupation);
                            White_txt();
                            printf("] ");
                        }
                        else {

                            printf("[");
                            Occupied_tile_txt();
                            printf("*****");
                            White_txt();
                            printf("] ");
                        }
                    }
                    //Program draws empty tile
                    else {
                        //Got two elements
                        if (GS->board[i - 1][j - 1].treasure != 0 && GS->board[i - 1][j - 1].artifact != 0) {
                            printf("[");
                            Yellow_I_txt();
                            printf("%dC", GS->board[i - 1][j - 1].treasure);
                            Green_I_txt();
                            switch (GS->board[i - 1][j - 1].artifact)
                            {
                            case HORSE:
                                printf(" Hr");
                                break;
                            case BROKEN_ARROW:
                                printf(" BA");
                                break;
                            case SPEAR:
                                printf(" Sp");
                                break;
                            }
                            White_txt();
                            printf("] ");
                        }
                        //Got no elements
                        else if (GS->board[i - 1][j - 1].treasure == 0 && GS->board[i - 1][j - 1].artifact == 0) {
                            printf("[");
                            printf("_____");
                            printf("] ");
                        }
                        //Got one element
                        else {
                            if (GS->board[i - 1][j - 1].treasure != 0) {
                                printf("[");
                                Yellow_I_txt();
                                printf("%dcoin", GS->board[i - 1][j - 1].treasure);
                                White_txt();
                                printf("] ");
                            }
                            else {
                                printf("[");
                                Green_I_txt();
                                switch (GS->board[i - 1][j - 1].artifact)
                                {
                                case HORSE:
                                    printf("Horse");
                                    break;
                                case BROKEN_ARROW:
                                    printf("B.Arr");
                                    break;
                                case SPEAR:
                                    printf("Spear");
                                    break;
                                }
                                White_txt();
                                printf("] ");
                            }
                        }
                    }
                }
            }
        }
        printf("\n");
    }
}

void order_scores(int number_of_players, player_data player[], player_data ranking[]) {

    /*copies the structure*/
    int i;
    for (i = 0; i < number_of_players; i++) {
        ranking[i].points = player[i].points;
    }

    /*bubble sort*/
    i = 0; int j = 0;
    for (int j = 0; j < number_of_players - 1; j++) {
        for (int i = 0; i + 1 < number_of_players - j; i++) {

            if (ranking[i].points < ranking[i + 1].points) {
                int temp = ranking[i].points;
                ranking[i].points = ranking[i + 1].points;
                ranking[i + 1].points = temp;
            }
        }
    }

    /* acscribes names to the new sorted ranking structure*/
    int previous;
    for (int j = 0; j < number_of_players; j++) {
        for (int i = 0; i < number_of_players; i++) {
            if (ranking[j].points == player[i].points && i != previous) {
                previous = i;
                ranking[j] = player[i];
                break;
            }
        }
    }
}