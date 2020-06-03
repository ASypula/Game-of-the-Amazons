#ifndef _Output_H
#define _Output_H

#include "Common.h"


void add_player_data_file(FILE* fp, struct game_state* GS);
/*
* Saves in file data about player_data
* @param *fp - file pointer
* @param *GS - game_state
*/

void add_size_file(FILE* fp, struct game_state* GS);
/*
* Saves in file data about size
* @param *fp - file pointer
* @param *GS - game_state
*/

void add_tiles_file(FILE* fp, struct game_state* GS);
/*
* Saves in file data about files
* @param *fp - file pointer
* @param *GS - game_state
*/

void save_data_file(char* file_name, struct game_state* GS);
/*
* Saves in file stored data from a game_state
* @param *file_name - name of the file
* @param *GS - game_state
*/

#endif // _Output_H