
/*******************************************************************************************
* Programmer: Marco Arceo                                                                      
* Class: CptS 121, Fall  2017; Lab Section 21                                    
* Programming Assignment: Statistical Analysis of Student Records                                                    
* Date: November 3rd, 2017                                                                         
* Description: Create the game of battleship
*******************************************************************************************/

#include "header.h"

void rules()
{ // This displays the rules of battleship
	printf("1. This is a two player game.\n");
	printf("2. Player 1 is you and Player 2 is the computer.\n");
	printf("3. There is a total of 5 ships in this game. \n");
	printf("4. Ships can only be placed horizontally or vertically.\n");
	printf("5. Ships can not overlap and must be placed in the grid. \n");
	printf("6. Once a ship is placed, the position can not be altered. \n");
	printf("7. On your turn, pick a coordiante and fire! \n");
	printf("8. Either a hit or miss will be produced. \n");
	printf("9. The first player to lose their ships loses. \n");
	printf("\nYou will now be directed back to the menu!\n\n");
}

void display_menu() // Displays the menu options
{ 
	int menu_option = 0;

	printf("WELCOME TO THE GAME OF BATTLESHIP!\n\n");
	printf("1. Display game rules\n");
	printf("2. Play Game\n");
	printf("3. Exit\n");
}

int get_option(void) // Gets the option from the user
{ // Used in previous PA's
	int option = 0, status = 0;

	status = scanf("%d", &option);
	if (status == 0)
	{
		printf("Failed at reading in an integer!\n");
	}
	return option;
}

int determine_option(void) // Determines if the option is valid
{ // Used in previous PA's
	int option = 0;

	do // input validation loop
	{
		display_menu();
		option = get_option();
		system("cls");
	} while ((option < 1) || (option > 3));

	return option;
}

int determine_player_sequence()
{ // Code is used to generate who goes first
	int start = 0;
	start = rand() % 2 + 1;

	if (start == 1)
	{
		printf("Player 1 was chosen to go first.\n\n");
		return start;
	}
	else if (start == 2)
	{
		printf("Player 2 was chosen to go first.\n\n");
		return start;
	}
}

void init_board(char board[][MAX_COLS], int num_rows, int num_cols)
{ // O'Fallon Code
	int row_index = 0, col_index = 0;

	for (; row_index < num_rows; ++row_index)
	{
		for (col_index = 0; col_index < num_cols; ++col_index)
		{
			board[row_index][col_index] = '~';
		}
	}
}

void print_board(char board[][MAX_COLS], int  num_rows, int num_cols)
{
	// I use some of Andy's Code and update it with my own ideas to build a complete grid
	int row_index = 0, col_index = 0, number = 0;

	printf(" ");
	for (col_index = 0; col_index < 10; ++col_index) // Displays letters on top of the grid
	{
		printf(" ");
		printf("%c%2d", ' ', number++);
	}
	putchar('\n');
	number = 0;

	for (row_index = 0; row_index < num_rows; ++row_index) // Displays the borders
	{
		for (col_index = -1; col_index < num_cols; ++col_index)
		{
			printf("%3c%c", '-', ' ');
		}
		putchar('\n');

		printf("%d ", number++);

		for (col_index = 0; col_index < num_cols; ++col_index)
		{
			printf("| %c ", board[row_index][col_index]);
		}
		putchar('|');
		putchar('\n');
	}

	for (col_index = -1; col_index < num_cols; ++col_index) // Displays the bottom of the border
	{
		printf("%3c%c", '-', ' ');
	}
	putchar('\n');
}

int user_ship_input(void)
{// Simple user input to give the option of a manual input or random input
	int choice = 0;
	
	do
	{
		printf("\nWould you like to 1.) Manually place your ships or 2.) Have your ships placed randomly?: ");
		scanf("%d", &choice);
		printf("\n\n");
	} while (choice > 2 && choice < 1);
	return choice;
}

Dir get_direction(void)
{ // Andy O'Fallon Class Code
	Dir direction = VERTICAL;

	direction = (Dir)(rand() % 2);

	return direction;
}

void generate_start_pt(int ship_length, Dir direction, int rows, int cols, int *row_st, int *col_st)
{ // Andy O'Fallon Class Code
	if (direction == HORIZONTAL)
	{
		*row_st = rand() % rows; // 0 - 9
		*col_st = rand() % (cols - ship_length + 1);
	}
	else
	{
		*row_st = rand() % (rows - ship_length + 1);
		*col_st = rand() % cols; // 0 - 9
	}
}

bool place_ship(char board[][MAX_COLS], int length, char symbol, int row_st, int col_st, Dir direction)
{ // Andy O'Fallon Class Code with a twist of my ideas to not let it overlap (I never got this code to work and this causes either an infinite loop or crashes the game)
	int index = 0;
	bool overlap = true;

	while (index < length)
	{

		do
		{
			if (direction == VERTICAL && board[row_st + index][col_st] == '~')
			{
				board[row_st + index][col_st] = symbol;
				overlap = false;
			}
			else if (direction == HORIZONTAL && board[row_st][col_st + index] == '~')
			{
				board[row_st][col_st + index] = symbol;
				overlap = false;
			}
			else
			{
				overlap = true;
			}
		} while (overlap == true);
		index++;
	}
}

int manual_ships(char board[][MAX_COLS])
{ // Code is courtesy of Seth Michel from Github, some variable names and lines were changed to suit my code

	char ship[50] = { '\0' }, letter = '\0', line = '\0';
	int ship_number = 1, direction = 0, size = 0, flag = 1, checker = 0,
		row_st = 0, col_st = 0, number = 0;

	for(; ship_number < 6; ship_number++) // Goes through the cases picking out the ships
	{
		switch (ship_number)
		{
		case 1:
			strcpy(ship, "Aircraft Carrier (5 Cells)");
			size = 5;
			letter = 'A';
			break;
		case 2:
			strcpy(ship, "Battleship (4 Cells)");
			size = 4;
			letter = 'B';
			break;
		case 3:
			strcpy(ship, "Cruiser (3 Cells)");
			size = 3;
			letter = 'C';
			break;
		case 4:
			strcpy(ship, "Submarine (3 Cells)");
			size = 3;
			letter = 'S';
			break;
		case 5:
			strcpy(ship, "Destroyer (2 Cells)");
			size = 2;
			letter = 'D';
			break;
		}

		do
		{ // This loop makes sure everything gets placed correctly on the board
			printf("Enter the starting point for %s in the format (2 3) for row and column: ", ship);
			scanf("%d%d", &row_st, &col_st);

			while (row_st > 10 && row_st < 0 && col_st > 10 && col_st < 0) // Placement check
			{
				printf("This point is not inside the grid, please enter a new point: ");
				scanf("%d%d", &row_st, &col_st);
			}

			while (board[row_st][col_st] != '~') // Overlap check
			{
				printf("There is already a ship occupying this space, please enter a new point: ");
				scanf("%d%d", &row_st, &col_st);
			}

			printf("What direction would you like to place the %s in?\nEnter 1 for right, 2 for left, 3 for up, 4 for down: ", ship);
			scanf("%d", &direction);

			while (direction != 1 && direction != 2 && direction != 3 && direction != 4) // Direction check
			{
				printf("Please select your direction:\nEnter 1 for right, 2 for left, 3 for up, 4 for down: ");
				scanf("%d", &direction);
			}

			row_st = row_st + 1;
			col_st = col_st + 1;

			if (direction == 1 && (col_st + size) < 10 && board[row_st][col_st + 1] == '~') // Placement check for right direction
			{
				if (size == 2)
				{
					checker = 1;
					flag = 0;
				}
				if (size == 3 && board[row_st][col_st + 2] == '~')
				{
					checker = 1;
					flag = 0;
				}
				if (size == 4 && board[row_st][col_st + 2] == '~' && board[row_st][col_st + 3] == '~')
				{
					checker = 1;
					flag = 0;
				}
				if (size == 5 && board[row_st][col_st + 2] == '~' && board[row_st][col_st + 3] == '~' && board[row_st][col_st + 4] == '~')
				{
					checker = 1;
					flag = 0;
				}
				if (checker == 0)
				{
					printf("This input is invalid. please choose a new cell.\n");
					flag = 1;
				}
				else if (checker == 1)
				{
					for (int i = 0; i < size; i++)
					{
						board[row_st - 1][col_st + i - 1] = letter;
					}
				}
			}

			else if (direction == 2 && (col_st - size) > 0 && board[row_st][col_st - 1] == '~') // Placement check for the left direction
			{
				if (size == 2)
				{
					checker = 1;
					flag = 0;
				}
				if (size == 3 && board[row_st][col_st - 2] == '~')
				{
					checker = 1;
					flag = 0;
				}
				else if (size == 4 && board[row_st][col_st - 2] == '~' && board[row_st][col_st - 3] == '~')
				{
					checker = 1;
					flag = 0;
				}
				else if (size == 5 && board[row_st][col_st - 2] == '~' && board[row_st][col_st - 3] == '~' && board[row_st][col_st - 4] == '~')
				{
					checker = 1;
					flag = 0;
				}

				if (checker == 0)
				{
					printf("This input is invalid. please choose a new cell.\n");
					flag = 1;
				}
				else if (checker == 1)
				{
					for (int i = 0; i < size; i++)
					{
						board[row_st - 1][col_st - 1 - i] = letter;
					}
				}
			}

			else if (direction == 3 && (row_st - size) > 0 && board[row_st - 1][col_st] == '~') // Placement check for the up direction
			{

				if (size == 2)
				{
					checker = 1;
					flag = 0;
				}
				if (size == 3 && board[row_st - 2][col_st] == '~')
				{
					checker = 1;
					flag = 0;
				}
				else if (size == 4 && board[row_st - 2][col_st] == '~' && board[row_st - 3][col_st] == '~')
				{
					checker = 1;
					flag = 0;
				}
				else if (size == 5 && board[row_st - 2][col_st] == '~' && board[row_st - 3][col_st] == '~' && board[row_st - 4][col_st] == '~')
				{
					checker = 1;
					flag = 0;
				}

				if (checker == 0)
				{
					printf("This input is invalid. please choose a new cell.\n");
					flag = 1;
				}
				else if (checker == 1)
				{
					for (int i = 0; i < size; i++)
					{
						board[row_st - 1 - i][col_st - 1] = letter;
					}
				}
			}
			
			else if (direction == 4 && (row_st + size) < 10 && board[row_st + 1][col_st] == '~') // Placement check for the down direction
			{
				if (size == 2)
				{
					checker = 1;
					flag = 0;
				}
				if (size == 3 && board[row_st + 2][col_st] == '~')
				{
					checker = 1;
					flag = 0;
				}
				else if (size == 4 && board[row_st + 2][col_st] == '~' && board[row_st + 3][col_st] == '~')
				{
					checker = 1;
					flag = 0;
				}
				else if (size == 5 && board[row_st + 2][col_st] == '~' && board[row_st + 3][col_st] == '~' && board[row_st + 4][col_st] == '~')
					checker = 1;
					flag = 0;

				if (checker == 0)
				{
					printf("This input is invalid. please choose a new cell.\n");
					flag = 1;
				}
				else if (checker == 1)
				{
					for (int i = 0; i < size; i++)
					{
						board[row_st - 1 + i][col_st - 1] = letter;
					}
				}
			}

			else  // Last check that determines if the ship goes out of bounds
			{
				printf("The direction you chose would take the %s out of the boundaries\n", ship);
				flag = 1;
				system("cls");
			}

		} while (flag == 1);
		system("cls");
		print_board(board, MAX_ROWS, MAX_COLS);
	}
}
		
int player_hit_or_miss(char board[][MAX_COLS], stats *player1_stats, ships *player1_ships, FILE *outfile)
{ // This code was written in the FIZ with minor help of the TA's
  // Ryan Manny helped me sort the code and place structs
	int shot_row = 0, shot_col = 0, hit = 0, invalid = 0, miss = 0;

	do
	{
		do
		{
			printf("Please enter the cell (0 0) you want to shoot at: ");
			scanf("%d%d", &shot_row, &shot_col);
			shot_row = shot_row + 1;
			shot_col = shot_col + 1;
		} while (shot_row > 10 || shot_row < 0 || shot_col > 10 || shot_col < 0);

		if (board[shot_row][shot_col] == 'm' || board[shot_row][shot_col] == '*')
		{
			invalid = 1;
		}
		else
		{
			invalid = 0;
			fprintf(outfile, "coorinates: %d %d", shot_row, shot_col);
		}

	} while (invalid == 1);

	if (board[shot_row][shot_col] == '~') //missed
	{
		printf("Your shot was a bust!\n");
		board[shot_row][shot_col] = 'm';
		player1_stats->misses++;
		fprintf(outfile, "misses: %d", player1_stats->misses);
	}
	else if (board[shot_row][shot_col] != '~') //hits a letter
	{
		if (board[shot_row][shot_col] == 'A')
		{
			printf("You hit a boat!\n");
			board[shot_row][shot_col] == '*';
			player1_stats->hits++;
			player1_ships->carrier++;
			fprintf(outfile, "hits: %d", player1_stats->hits);
		}
		if (board[shot_row][shot_col] == 'B')
		{
			printf("You hit a boat!\n");
			board[shot_row][shot_col] == '*';
			player1_stats->hits++;
			player1_ships->battleship++;
			fprintf(outfile, "hits: %d", player1_stats->hits);
		}

		if (board[shot_row][shot_col] == 'C')
		{
			printf("You hit a boat!\n");
			board[shot_row][shot_col] == '*';
			player1_stats->hits++;
			player1_ships->cruiser++;
			fprintf(outfile, "hits: %d", player1_stats->hits);
		}

		if (board[shot_row][shot_col] == 'S')
		{
			printf("You hit a boat!\n");
			board[shot_row][shot_col] == '*';
			player1_stats->hits++;
			player1_ships->submarine++;
			fprintf(outfile, "hits: %d", player1_stats->hits);
		}

		if (board[shot_row][shot_col] == 'D')
		{
			printf("You hit a boat!\n");
			board[shot_row][shot_col] == '*';
			player1_stats->hits++;
			player1_ships->destroyer++;
			fprintf(outfile, "hits: %d", player1_stats->hits);
		}
	}
}

int computer_hit_or_miss(char board[][MAX_COLS], stats *player2_stats, ships *player2_ships, FILE *outfile)
{ // This code was written in the FIZ with minor help of the TA's
  // Ryan Manny helped me sort the code and place structs
	int shot_row = 0, shot_col = 0, miss = 0, invalid = 0, hit = 0;

	do
	{
		shot_row = rand() % 10;
		shot_col = rand() % 10;

		if (board[shot_row][shot_col] == 'm' || board[shot_row][shot_col] == "*")
		{
			invalid = 1;
		}
		else
		{
			invalid = 0;
			fprintf(outfile, "coorinates: %d %d", shot_row, shot_col);
		}
	} while (invalid == 1);

	if (board[shot_row][shot_col] == '~')
	{
		printf("Your shot was a bust!\n");
		board[shot_row][shot_col] = 'm';
		player2_stats->misses++;
		fprintf(outfile, "misses: %d", player2_stats->misses);
	}

	else if (board[shot_row][shot_col] != '~')
	{
		if (board[shot_row][shot_col] != '~') //hits a letter
		{
			if (board[shot_row][shot_col] == 'A') 
			{
				printf("You hit a boat!\n");
				board[shot_row][shot_col] == '*';
				player2_stats->hits++;
				player2_ships->carrier++;
				fprintf(outfile, "hits: %d", player2_stats->hits);
			}
			if (board[shot_row][shot_col] == 'B')
			{
				printf("You hit a boat!\n");
				board[shot_row][shot_col] == '*';
				player2_stats->hits++;
				player2_ships->battleship++;
				fprintf(outfile, "hits: %d", player2_stats->hits);
			}
				
			if (board[shot_row][shot_col] == 'C')
			{
				printf("You hit a boat!\n");
				board[shot_row][shot_col] == '*';
				player2_stats->hits++;
				player2_ships->cruiser++;
				fprintf(outfile, "hits: %d", player2_stats->hits);
			}
				
			if (board[shot_row][shot_col] == 'S')
			{
				printf("You hit a boat!\n");
				board[shot_row][shot_col] == '*';
				player2_stats->hits++;
				player2_ships->submarine++;
				fprintf(outfile, "hits: %d", player2_stats->hits);
			}

			if (board[shot_row][shot_col] == 'D')
			{
				printf("You hit a boat!\n");
				board[shot_row][shot_col] == '*';
				player2_stats->hits++;
				player2_ships->destroyer++;
				fprintf(outfile, "hits: %d", player2_stats->hits);
			}
		}
	}
}

bool winner(stats *player1_stats, stats *player2_stats, bool game)
{ // Determines if there is a winner
	if (player1_stats->hits == 17)
	{
		printf("Player 1 is the winner!\n");
		game = false;
		return game;
	}
	else if (player2_stats->hits == 17)
	{
		printf("Player 2 is the winner!\n");
		game = false;
		return game;
	}
	else
	{
		return game;
	}
}