
/*******************************************************************************************
* Programmer: Marco Arceo                                                                      
* Class: CptS 121, Fall  2017; Lab Section 21                                    
* Programming Assignment: Statistical Analysis of Student Records                                                    
* Date: November 3rd, 2017                                                                         
* Description: Create the game of battleship
*******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ROWS 10
#define MAX_COLS 10

typedef enum dir
{
	VERTICAL, HORIZONTAL
}Dir;

typedef struct stats
{
	int hits;
	int misses;
}stats;

typedef struct ships
{
	int carrier;
	int battleship;
	int cruiser;
	int submarine;
	int destroyer;
}ships;

void rules();
void display_menu();
void rules();
void display_menu();
int get_option(void);
int determine_option(void);
int determine_player_sequence();
void init_board(char board[][MAX_COLS], int num_rows, int num_cols);
void print_board(char board[][MAX_COLS], int  num_rows, int num_cols);
int user_ship_input(void);
Dir get_direction(void);
void generate_start_pt(int ship_length, Dir direction, int rows, int cols, int *row_st, int *col_st);
bool place_ship(char board[][MAX_COLS], int length, char symbol, int row_st, int col_st, Dir direction);
int manual_ships(char board[][MAX_COLS]);
int player_hit_or_miss(char board[][MAX_COLS], stats *player1_stats, ships *player1_ships, FILE *outfile);
int computer_hit_or_miss(char board[][MAX_COLS], stats *player2_stats, ships *player2_ships, FILE *outfile);
bool winner(stats *player1_stats, stats *player2_stats, bool game);