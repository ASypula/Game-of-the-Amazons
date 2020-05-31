#include "Input.h"



int place_amazons(game_state *GS){
    
    int id = find_ID(GS);
    int *x, *y;
    
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

tile get_tile_file(FILE* fp, struct game_state* GS) {

	tile temp;
	int c;
	int buffer[10]; // 3 digit tile
	int count = 0;

	do {
		c = getc(fp);

		if (c != ' ' && c != '\n') {
			if (count >= 3) {
				//Exception
				printf("Error in reading tile, tile has more than 3 digits!\n");
				GS->error = 1;
			}

			buffer[count++] = c;
		}
		else if (count > 0) {

			temp.treasure = number(buffer[0]);
			if (temp.treasure > 5 || temp.treasure < 0) {
				printf("Error in reading tile, wrong value of treasure tile!\n");
				GS->error = 1;
			}
			temp.artifact = number(buffer[1]);
			if (temp.artifact > 3 || temp.artifact < 0) {
				printf("Error in reading tile, wrong value of artifact tile!\n");
				GS->error = 1;
			}
			temp.occupation = number(buffer[2]);
			if (temp.occupation > 9 || temp.occupation < 0) {
				printf("Error in reading tile, wrong value of occupation tile!\n");
				GS->error = 1;
			}

			count = 0;
		}
	} while (c != ' ' && c!= EOF);

	return temp;
}

void get_board_file(FILE* fp, struct game_state* GS) {

	int i, j;
	for (i = 0; i < GS->fixed.height; i++) {
		for (j = 0; j < GS->fixed.width; j++) {
			GS->board[i][j] = get_tile_file(fp, GS);
		}
	}
}

void get_player_data_file(FILE* fp, struct game_state* GS) {
	
	getc(fp); // Just to get previous '\n'

	int c;
	int count = 0;
	int lines = 0;
	int type = 0; // 0 - name, 1 - ID, 2 - points
	char bufor[16];

	do {

		c = getc(fp);

		if (c == '\n') {
			lines++;
		}
		else {
			if (c != ' ' && c != '\n') {

				if (type == 0 && count >= 15) {
					printf("Error! Readed name has more that 15 chars!\n");
				}

				if (type == 2 && count >= 15) {
					printf("Error! Points number has more than 15 digits, unable to read!\n");
				}

				if (type == 0) {
					GS->player_list[lines].name[count++] = (char)c;
				}
				else if (type == 1 || type == 2) {
					bufor[count++] = (char)c;
					if (c < 48 || c > 57) {
						printf("Error! Score of a player cointains a char!\n");
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
					type = 0;
				}

				count = 0;
			}
		}
	} while (c != EOF);

	GS->fixed.number_of_players = lines;
}

void read_file(char* file_name, struct game_state* GS){

	// HEIGHT

	FILE* fp = fopen(file_name, "r");
	
	if (fp == NULL) {
		printf("Error in opening file!");
		GS->error = 1;
	}
	else {
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

		GS->player_list = (int*)malloc(sizeof(player_data) * 8);

		// BOARD

		get_board_file(fp, GS);

		// PLAYER DATA

		get_player_data_file(fp, GS);

		fclose(fp);
	}
}

int found_horse (game_state* GS, int *dx, int*dy, int x, int y) {
    int found = 0;
    int i, j;
    for (i = x; (i < GS->fixed.width) && !found; i++)
    {
        for (j = y; (j < GS->fixed.height) && !found; j++)
        {
            if (GS->board[i][j].artifact == HORSE)
            {
                *dx = i;
                *dy = j;
                found = 1;
            }
        }
    }
    return found;
}

int max_point (game_state* GS, int *dx, int*dy, int x, int y, int search_max)
{
    int i, j;
    int max_found = 0;
    for (i = x; (i < GS->fixed.width) && (!max_found); i++)
    {
        for (j = y; (j < GS->fixed.height) && (!max_found); j++)
        {
            if (GS->board[i][j].treasure == search_max)
            {
                *dx = i;
                *dy = j;
                max_found = 1;
            }
        }
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
    int x = 0;
    int y = 0;
    int *dx;
    int *dy;
    int max_search = 5;  //maximum value of treasure
    int good_place = 0;
    while (found_horse(GS, dx, dy, x, y) && !(good_place = tile_available(GS, *dx, *dy, found_x, found_y)))
    {
        x = *dx + 1;
        y = *dy;
    }
    if (!good_place)
    {
        while (max_point(GS, dx, dy, x, y, max_search) && !(good_place = tile_available(GS, *dx, *dy, found_x, found_y) && max_search >= 0)
        {
            x = *dx + 1;
            y = *dy;
            if ((x == GS->fixed.width) && (y == GS->fixed.height))
            {
                x = *dx = 0;
                y = *dy = 0;
                max_search--;
            }
        }
    }
    return good_place;
}
