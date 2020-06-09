#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Movement.h"
#include "Input.h"
#include "Common.h"
#include "Output.h"

int get_multi_digit_file(FILE* fp, game_state *GS) {

	int c;
	char buffer[12]; // Max 10 digit number
	int count = 0;
	int number;

	do {
		c = getc(fp);

		if (c != '\n' && c != ' ' && c != EOF) {
			if (count >= 11) {
				printf("Error! Size number has more that 10 digits, unable to read!\n");
				GS->error = 1;
			}

			buffer[count++] = (char)c;
		}
		else if (count > 0) {
			buffer[count] = 0;

			number = atoi(buffer);
			if (number < 0) {
				printf("Error! Size number is negative!\n");
				GS->error = 1;
			}

			count = 0;
		}
	} while (c != '\n' && c != ' ' && c != EOF);

	return number;
}

tile get_tile_file(FILE* fp, struct game_state* GS, int i, int j) {

    tile temp;
    int c;
    int buffer[10]; // 3 digit tile
    int count = 0;

    do {
        c = getc(fp);

        if (c != ' ' && c != '\n' && c != EOF) {
            if (count >= 3) {
                //Exception
                printf("Error in reading tile[%d][%d], tile has more than 3 digits!\n", i, j);
                GS->error = 1;
            }

            buffer[count++] = c;
        }
        else if (count > 0) {

            temp.treasure = number(buffer[0]);
            if (temp.treasure > 5 || temp.treasure < 0) {
                printf("Error in reading tile[%d][%d], wrong value of treasure tile!\n", i, j);
                GS->error = 1;
            }
            temp.artifact = number(buffer[1]);
            if (temp.artifact > 3 || temp.artifact < 0) {
                printf("Error in reading tile[%d][%d], wrong value of artifact tile!\n", i, j);
                GS->error = 1;
            }
            temp.occupation = number(buffer[2]);
            if (temp.occupation > 9 || temp.occupation < 0) {
                printf("Error in reading tile[%d][%d], wrong value of occupation tile!\n", i, j);
                GS->error = 1;
            }
            if ((temp.occupation > 0 && temp.occupation < 9)&& (temp.treasure != 0 || temp.artifact != 0)) {
                printf("Occupied Tile[%d][%d], has: ", i, j);
                if (temp.treasure != 0) {
                    printf("treasure=%d ", temp.treasure);
                }
                if (temp.artifact != 0) {
                    printf("artifact=%d ", temp.artifact);
                }
                printf("\n");
                GS->error = 1;
            }
            count = 0;
        }
    } while (c != ' ' && c != '\n' && c != EOF);

    return temp;
}

void get_board_file(FILE* fp, struct game_state* GS) {

	int i, j;
	for (i = 0; i < GS->fixed.height; i++) {
		for (j = 0; j < GS->fixed.width; j++) {
			GS->board[i][j] = get_tile_file(fp, GS, i, j);
		}
	}
}

void get_player_data_file(FILE* fp, struct game_state* GS) {

    int c;
    int count = 0;
    int lines = 0;
    int type = 0; // 0 - name, 1 - ID, 2 - points
    char bufor[16];

    do {

        c = getc(fp);

        if (c != ' ' && c != '\n' && c != EOF) {

            if (type == 0 && count >= 15) {
                printf("Error! Readed name has more that 15 chars!\n");
                GS->error = 1;
            }

            if (type == 2 && count >= 15) {
                printf("Error! Points number has more than 15 digits, unable to read!\n");
                GS->error = 1;
            }

            if (type == 0) {
                GS->player_list[lines].name[count++] = (char)c;
            }
            else if (type == 1 || type == 2) {
                bufor[count++] = (char)c;
                if (c < 48 || c > 57) {
                    printf("Error! Score of a player cointains a char!\n");
                    GS->error = 1;
                }
            }

        }
        else if (count > 0) {

            if (type == 0) {
                GS->player_list[lines].name[count] = 0; // Null at the end of a string
                type = 1;
            }
            else if (type == 1) {
                bufor[count] = 0;
                GS->player_list[lines].ID = atoi(bufor);
                if (GS->player_list[lines].ID < 0 || GS->player_list[lines].ID > 8) {
                    printf("Error! Wrong value of player ID!\n");
                    GS->error = 1;
                }
                type = 2;
            }
            else if (type == 2) {
                bufor[count] = 0;
                GS->player_list[lines].points = atoi(bufor);
                if (GS->player_list[lines].ID < 0) {
                    printf("Error! Negative value of player's points!\n");
                    GS->error = 1;
                }
                type = 0;
                lines++;
            }

            count = 0;
        }

    } while (c != EOF);

    GS->fixed.number_of_players = lines;

    int i, j;
    for (i = 0; i < GS->fixed.height; i++) {
        for (j = 0; j < GS->fixed.width; j++) {
            if (GS->board[i][j].occupation > GS->fixed.number_of_players && GS->board[i][j].occupation != MISSILE) {
                printf("Boards contains a pawn of undeclared player! ID:%d, Tile:[%d][%d]\n", GS->board[i][j].occupation, i, j);
                GS->error = 1;
            }
        }
    }
}

void add_user_initation(struct game_state* GS){

        int i;
		int on_list = 0;

		for(i=0; i<GS->fixed.number_of_players; i++){
            if(!strcmp(GS->name, GS->player_list[i].name)){
                on_list = 1;
            }
		}

        i = 0;
		if(!on_list){
            while(GS->name[i]){
                printf("%c", GS->name[i]);
                GS->player_list[GS->fixed.number_of_players].name[i] = GS->name[i];
                i++;
            }
            GS->player_list[GS->fixed.number_of_players].name[i] = 0;
            //GS->player_list[GS->fixed.number_of_players].name = GS->name;
            GS->player_list[GS->fixed.number_of_players].ID = (GS->fixed.number_of_players + 1);
            GS->player_list[GS->fixed.number_of_players].points = 0;

            GS->fixed.number_of_players++;
		}
}

void read_file(char* file_name, struct game_state* GS){

	FILE* fp = fopen(file_name, "r+");

	if (fp == NULL) {
		printf("Error in opening file!");
		GS->error = 1;
	}
	else {

        // HEIGHT

		GS->fixed.height = get_multi_digit_file(fp, GS);

		// WIDTH

		GS->fixed.width = get_multi_digit_file(fp, GS);

		// ALLOCATING MEMORY FOR THE BOARD

		GS->board = malloc(GS->fixed.height * sizeof(**(GS->board)));
		int p = 0;
		while (p < GS->fixed.height) {
			*(GS->board + p) = malloc(GS->fixed.width * sizeof(**(GS->board)));
			p++;
		}

		// ALLOCATING MEMORY FOR THE PLAYER_DATA

		GS->player_list = (player_data*)malloc(sizeof(player_data) * 8);

		// BOARD

		get_board_file(fp, GS);

		// PLAYER DATA

		get_player_data_file(fp, GS);

		//Adding name if needed

		add_user_initation(GS);

		fclose(fp);
	}
}

int found_horse (game_state* GS, int *dx, int*dy, int x, int y) {
    int found = 0;
    int i, j;
    if (x == 0)
    {
        for (i = 0; (i < GS->fixed.height) && !found; i++)
        {
            for (j = 0; (j < GS->fixed.width) && !found; j++)
            {
                if (GS->board[i][j].artifact == HORSE)
                {
                    *dx = i;
                    *dy = j;
                    found = 1;
                }
            }
        }
    }
    else
    {
        for (j = y; (j < GS->fixed.width) && !found; j++)
            {
                if (GS->board[x][j].artifact == HORSE)
                {
                    *dx = x;
                    *dy = j;
                    found = 1;
                }
            }
        for (i = x+1; (i < GS->fixed.height) && !found; i++)
        {
            for (j = 0; (j < GS->fixed.width) && !found; j++)
            {
                if (GS->board[i][j].artifact == HORSE)
                {
                    *dx = i;
                    *dy = j;
                    found = 1;
                }
            }
        }
    }
    return found;
}


int max_point (game_state* GS, int *dx, int*dy, int x, int y, int search_max)
{
    int i, j;
    int max_found = 0;
    for (i = x; (i < GS->fixed.height) && (!max_found); i++)
    {
        for (j = y; (j < GS->fixed.width) && (!max_found); j++)
        {
            if (GS->board[i][j].treasure == search_max)
            {
                *dx = i;
                *dy = j;
                max_found = 1;
            }
        }
    }
    if (!max_found)
    {
        *dx = i;
        *dy = j;
    }
    return max_found;
}


int tile_available (game_state* GS, int x, int y, int *found_x, int *found_y)
{
    if (point_in_board(GS, x-1, y) && GS->board[x-1][y].occupation == FREE)
    {
        *found_x = x-1;
        *found_y = y;
        return 1;
    }
    else if (point_in_board(GS, x-1, y-1) && GS->board[x-1][y-1].occupation == FREE)
    {
        *found_x = x-1;
        *found_y = y-1;
        return 1;
    }
    else if (point_in_board(GS, x, y-1) && GS->board[x][y-1].occupation == FREE)
    {
        *found_x = x;
        *found_y = y-1;
        return 1;
    }
    else if (point_in_board(GS, x+1, y-1) && GS->board[x+1][y-1].occupation == FREE)
    {
        *found_x = x+1;
        *found_y = y-1;
        return 1;
    }
    else if (point_in_board(GS, x+1, y) && GS->board[x+1][y].occupation == FREE)
    {
        *found_x = x+1;
        *found_y = y;
        return 1;
    }
    else if (point_in_board(GS, x+1, y+1) && GS->board[x+1][y+1].occupation == FREE)
    {
        *found_x = x+1;
        *found_y = y+1;
        return 1;
    }
    else if (point_in_board(GS, x, y+1) && GS->board[x][y+1].occupation == FREE)
    {
        *found_x = x;
        *found_y = y+1;
        return 1;
    }
    else if (point_in_board(GS, x-1, y+1) && GS->board[x-1][y-1].occupation == FREE)
    {
        *found_x = x-1;
        *found_y = y+1;
        return 1;
    }
    else
        return 0;
}

int best_place (game_state* GS, int *found_x, int *found_y)
{
    int x, y;
    if (GS->already_placed_amazons == 0)
    {
        x = 0;
        y = 0;
    }
    else
    {
        x = GS->positions[GS->already_placed_amazons - 1].x + 1;
        y = GS->positions[GS->already_placed_amazons - 1].y + 1;
    }
    int *dx;
    dx = (int*) malloc (sizeof(int));
    int *dy;
    dy = (int*) malloc (sizeof(int));
    *dx = x;
    *dy = y;
    int max_search = 5;  //maximum value of treasure
    int no_place = 1;
    while (no_place && found_horse(GS, dx, dy, x, y))
    {
        if (!(tile_available(GS, *dx, *dy, found_x, found_y)))
        {
            if (*dx >= GS->fixed.height)
            {
                *dx = -1;
                (*dy)++;
            }
            x = *dx + 1;
            y = *dy;
        }
        else
        {
            no_place = 0;
        }
    }
    if (no_place)
    {
        while (no_place)
        {
            while (max_search >= 0 && !max_point(GS, dx, dy, x, y, max_search))
            {
                if ((*dx == GS->fixed.height) && (*dy == GS->fixed.width))
                {
                    x = *dx = 0;
                    y = *dy = 0;
                    max_search--;
                }
                else if (*dx = GS->fixed.height)
                {
                    *dx = 0;
                    *dy++;
                }
                else
                {
                    x = *dx + 1;
                    y = *dy;
                }
            }
            if(max_point(GS, dx, dy, x, y, max_search) && tile_available(GS, *dx, *dy, found_x, found_y) && max_search > 0)
                no_place = 0;
            else
            {
                if (*dx >= GS->fixed.height)
                {
                    *dx = -1;
                    *dy++;
                }
                x = *dx + 1;
                y = *dy;
            }
        }
    }
    if (no_place)
        return 0;
    else
        return 1;
}


int place_amazons(game_state *GS){

    int id = find_ID(GS);
    int *x;
    x = (int*) malloc (sizeof(int));
    int *y;
    y = (int*) malloc (sizeof(int));
    find_amazons(GS);

    if(GS->already_placed_amazons < GS->fixed.number_of_pawns){
        if (best_place (GS, x, y))
        {
            GS->board[*x][*y].treasure = FREE;
            GS->board[*x][*y].artifact = FREE;
            GS->board[*x][*y].occupation = id;
            GS->already_placed_amazons++;
            return 1;
        }
        else
        {
            printf ("There is no valid tile to place an amazon.\n");
            return 0;
        }
    }
    else
    {
        printf ("All amazons are already placed on the board.\n");
        return 0;
    }
}



