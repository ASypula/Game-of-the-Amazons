#include "Output.h"

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

void draw_board(struct game_state* GS) {
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
                            printf("Amaz%d", GS->board[i - 1][j - 1].occupation);
                            printf("] ");
                        }
                        else {

                            printf("[");
                            printf("*****");
                            printf("] ");
                        }
                    }
                    //Program draws empty tile
                    else {
                        //Got two elements
                        if (GS->board[i - 1][j - 1].treasure != 0 && GS->board[i - 1][j - 1].artifact != 0) {
                            printf("[");
                            printf("%dC", GS->board[i - 1][j - 1].treasure);
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
                                printf("%dcoin", GS->board[i - 1][j - 1].treasure);
                                printf("] ");
                            }
                            else {
                                printf("[");
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

void order_scores( game_state *GS ){

  /*copies the structure*/
    state.ranking = (int *) malloc(sizeof(int) * state.fixed.number_of_players));

    int i;
    for (i = 0; i < GS->fixed.number_of_players; i++) {
        ranking[i] = player_list[i];
    }

  /*bubble sort*/
    i = 0;
    int j = 0;
    for (int j = 0; j < GS->fixed.number_of_players - 1; j++) {
        for (int i = 0; i + 1 < GS->fixed.number_of_players- j; i++) {

            if (ranking[i].points < ranking[i + 1].points) {
                player_data temp[8];
                temp[0] = ranking[i];
                ranking[i] = ranking[i + 1];
                ranking[i + 1] = temp[0];
            }
        }
    }

}

void add_player_data_file(FILE* fp, struct game_state* GS) {
    int i;

    for (i = 0; i < GS->fixed.number_of_players; i++) {
        fprintf(fp, "%s ", GS->player_list[i].name);
        fprintf(fp, "%d ", GS->player_list[i].ID);
        fprintf(fp, "%d ", GS->player_list[i].points);
        fprintf(fp, "\n");

    }
}

void add_size_file(FILE* fp, struct game_state* GS) {
    fprintf(fp, "%d %d\n", GS->fixed.height, GS->fixed.width);
}

void add_tiles_file(FILE* fp, struct game_state* GS) {
    int i, j;

    for (i = 0; i < GS->fixed.height; i++) {
        for (j = 0; j < GS->fixed.width; j++) {
            fprintf(fp, "%d%d%d ", GS->board[i][j].treasure, GS->board[i][j].artifact, GS->board[i][j].occupation);
        }
        fprintf(fp, "\n");
    }
}

void save_data_file(char* file_name, struct game_state* GS) {

    FILE* fp = fopen(file_name, "w");

    //Printing size

    add_size_file(fp, GS);

    //Printing tiles

    add_tiles_file(fp, GS);

    //Printing player data

    add_player_data_file(fp, GS);

    fclose(fp);
}