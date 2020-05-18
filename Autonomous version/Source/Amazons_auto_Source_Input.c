#include "Input.h"



int place_amazons(game_state *GS){
    
    if(GS->already_placed_amazons < GS->fixed.number_of_pawns){

        do {
            int chosen_row= rand()%GS->fixed.height;
            int chosen_column= rand()%GS->fixed.width;
        } while (GS->board[chosen_row][chosen_column].occupation != FREE || chosen_row > GS->fixed.height || chosen_column > GS->fixed.width);

        GS->board[chosen_row][chosen_column].treasure = FREE;
        GS->board[chosen_row][chosen_column].artifact = FREE;
        GS->board[chosen_row][chosen_column].occupation = GS->player_list[i].ID;
        GS->already_placed_amazons++;
        return 0;
    }
    return 1;
}

void choose_tile(game_state* GS, int* x, int* y) {
    int sign;
    int* symbol = &sign;
    *symbol = _getch();
    while (_kbhit())
    {
        *symbol = _getch();
    }

    switch (*symbol)
    {
        //LEFT
    case 75:
        if (*y == 0) {
            Red_I_txt();
            printf("You can't move on negative tile!\n");
            White_txt();
        }
        else {
            *y -= NORMAL_MOVE;
        }
        break;
        //CTRL + LEFT
    case 115:
        if (*y - CTRL_MOVE < 0) {
            Red_I_txt();
            printf("You can't move on negitve tile!\n");
            White_txt();
        }
        else {
            *y -= CTRL_MOVE;
        }
        break;
        //RIGHT
    case 77:
        if (*y == GS->fixed.width) {
            Red_I_txt();
            printf("You can't move out of the board!\n");
            White_txt();
        }
        else {
            *y += NORMAL_MOVE;
        }
        break;
        //CTRL + RIGHT
    case 116:
        if (*y + CTRL_MOVE > GS->fixed.width) {
            Red_I_txt();
            printf("You can't move out of the board!\n");
            White_txt();
        }
        else
        {
            *y += CTRL_MOVE;
        }
        break;
        //DOWN
    case 80:
        if (*x == GS->fixed.height)
        {
            Red_I_txt();
            printf("You can't move out of the board!\n");
            White_txt();
        }
        else
        {
            *x += NORMAL_MOVE;
        }
        break;
        //CTRL + DOWN
    case 145:
        if (*x + CTRL_MOVE > GS->fixed.height)
        {
            Red_I_txt();
            printf("You can't move out of the board!\n");
            White_txt();
        }
        else
        {
            *x += CTRL_MOVE;
        }
        break;
        //UP
    case 72:
        if (*x == 0)
        {
            Red_I_txt();
            printf("You can't move on negitve tile!\n");
            White_txt();
        }
        else {
            *x -= NORMAL_MOVE;
        }
        break;
        //CTRL + UP
    case 141:
        if (*x - CTRL_MOVE < 0) {
            Red_I_txt();
            printf("You can't move on negitve tile!\n");
            White_txt();
        }
        else {
            *x -= CTRL_MOVE;
        }
        break;

        //Error message
    default:
        Red_I_txt();
        printf("Use arrow keys to change tile!\n");
        White_txt();
        break;
    }
}

void get_move_with_arrowkey(game_state* GS, int* x, int* y) {
    int symbol;

    printf("To choose tile use arrowkeys\n");

    do {

        draw_board_color(GS);

        choose_tile(GS, x, y);

        //printf("Selected tile: [%d] [%d]\n", *x, *y);
        printf("Selected tile: [");
        White_bold_txt();
        printf("%d", *x);
        White_txt();
        printf("] [");
        White_bold_txt();
        printf("%d", *y);
        White_txt();
        printf("] \n");

        printf("To confirm, press enter.\n");
        printf("To move by 5 tiles use a combination of ctrl and arrow!");

        symbol = _getch();

        system("cls");

    } while (symbol != 13); // Ends with ENTER symbol

}

int get_multi_digit_file(FILE* fp) {

	int c;
	char buffer[12]; // Max 10 digit number
	int count = 0;
	int number;

	do {
		c = getc(fp);

		if (c != '\n' && c != ' ' && c != EOF) {
			if (count >= 11) {
				//Exception
			}

			buffer[count++] = (char)c;
		}
		else if (count > 0) {
			buffer[count] = 0;

			number = atoi(buffer);

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
			if (count >= 2) {
				//Exception
			}

			buffer[count++] = c;
		}
		else if (count > 0) {

			temp.treasure = number(buffer[0]);
			temp.artifact = number(buffer[1]);
			temp.occupation = number(buffer[2]);

		}
	} while (c != ' ');

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
	char bufor[15];

	do {

		c = getc(fp);

		if (c == '\n') {
			lines++;
		}
		else {
			if (c != ' ' && c != '\n') {

				if (type == 0) {
					GS->player_list[lines].name[count++] = (char)c;
				}
				else if (type == 1 || type == 2) {
					bufor[count++] = (char)c;
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
	
	GS->fixed.height = get_multi_digit_file(fp);

	// WIDTH

	GS->fixed.width = get_multi_digit_file(fp);

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
