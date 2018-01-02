
/*******************************************************************************************
* Programmer: Marco Arceo                                                                      
* Class: CptS 121, Fall  2017; Lab Section 21                                    
* Programming Assignment: Statistical Analysis of Student Records                                                    
* Date: November 3rd, 2017                                                                         
* Description: Create the game of battleship
*******************************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Game is not fully operating due to place_ship function, all other code should fullfil PA6 requirements!!
///////////////////////////////////////////////////////////////////////////////

#include "header.h"

int main(void)
{
	char player1_board[MAX_ROWS][MAX_COLS] = { {'~'} }, player2_board[MAX_ROWS][MAX_COLS] = { {'~'} }, temp_player1[MAX_ROWS][MAX_COLS], temp_player2[MAX_ROWS][MAX_COLS];
	srand((unsigned int)time(NULL));

	enum dir direction = VERTICAL;
	Dir direction2 = HORIZONTAL;
	int col_st = 0, row_st = 0, option = 0, start = 0, choice = 0, init_players = 0;
	stats player1_stats, player2_stats;
	ships player1_ships, player2_ships;

	FILE  *outfile = NULL;
	outfile = fopen("stats.txt", "w");

	bool game = true;

	do
	{
		option = determine_option();
		switch (option)
		{
		case 1: rules();
			system("pause");
			system("cls");
			break;
		case 3: printf("Goodbye!\n");
			game = false;
			return 0;
		}
	} while (option != 2 && option != 3);

	// Pauses the system and clears the screen
	system("pause");
	system("cls");

	// Initialize the boards for the player and computer
	init_board(player1_board, MAX_ROWS, MAX_COLS);
	init_board(player2_board, MAX_ROWS, MAX_COLS);


	// Determines which player goes first
	start = determine_player_sequence();
	system("pause");
	system("cls");

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (;init_players < 2; init_players++)
	{
		if (start == 1)// Player 1
		{
			printf("PLAYER 1: \n\n");
			choice = user_ship_input();

			if (choice == 1)
			{
				manual_ships(player1_board);
			}

			else if (choice == 2)
			{
				direction = get_direction();
				generate_start_pt(5, direction, MAX_ROWS, MAX_COLS, &row_st, &col_st);
				place_ship(player1_board, 5, 'A', row_st, col_st, direction);

				direction = get_direction();
				generate_start_pt(4, direction, MAX_ROWS, MAX_COLS, &row_st, &col_st);
				place_ship(player1_board, 4, 'B', row_st, col_st, direction);

				direction = get_direction();
				generate_start_pt(3, direction, MAX_ROWS, MAX_COLS, &row_st, &col_st);
				place_ship(player1_board, 3, 'C', row_st, col_st, direction);

				direction = get_direction();
				generate_start_pt(3, direction, MAX_ROWS, MAX_COLS, &row_st, &col_st);
				place_ship(player1_board, 3, 'S', row_st, col_st, direction);

				direction = get_direction();
				generate_start_pt(2, direction, MAX_ROWS, MAX_COLS, &row_st, &col_st);
				place_ship(player1_board, 2, 'D', row_st, col_st, direction);
				print_board(player1_board, MAX_ROWS, MAX_COLS);
				putchar('\n');
				system("pause");
				system("cls");
				start = 2;
			}
			temp_player1[MAX_ROWS][MAX_COLS] = player1_board; // Makes a copy of the players board
		}

		else // Player 2
		{
			printf("Player 2: \n\n");
			direction = get_direction();
			generate_start_pt(5, direction, MAX_ROWS, MAX_COLS, &row_st, &col_st);
			place_ship(player2_board, 5, 'A', row_st, col_st, direction);

			direction = get_direction();
			generate_start_pt(4, direction, MAX_ROWS, MAX_COLS, &row_st, &col_st);
			place_ship(player2_board, 4, 'B', row_st, col_st, direction);

			direction = get_direction();
			generate_start_pt(3, direction, MAX_ROWS, MAX_COLS, &row_st, &col_st);
			place_ship(player2_board, 3, 'C', row_st, col_st, direction);

			direction = get_direction();
			generate_start_pt(3, direction, MAX_ROWS, MAX_COLS, &row_st, &col_st);
			place_ship(player2_board, 3, 'S', row_st, col_st, direction);

			direction = get_direction();
			generate_start_pt(2, direction, MAX_ROWS, MAX_COLS, &row_st, &col_st);
			place_ship(player2_board, 2, 'D', row_st, col_st, direction);

			// print_board(player2_board, MAX_ROWS, MAX_COLS);
			printf("The computers board has been generated\n");
			temp_player2[MAX_ROWS][MAX_COLS] = player2_board; // Makes a copy of the computers board
			system("pause");
			system("cls");
			start = 1;
		}
	}

	do
	{
		if (start == 1)
		{
			print_board(temp_player2, MAX_ROWS, MAX_COLS);
			player_hit_or_miss(temp_player2, &player1_stats, &player1_ships, outfile);
			winner(&player1_stats, &player2_stats, game);
			start = 2;
		}
		else
		{
			
			computer_hit_or_miss(temp_player1, &player1_stats, &player1_ships, outfile);
			winner(&player1_stats, &player2_stats, game);
			start = 1;
			print_board(temp_player1, MAX_ROWS, MAX_COLS);
		}

	}while (game == true);

	fclose(outfile);
	return 0;
}
