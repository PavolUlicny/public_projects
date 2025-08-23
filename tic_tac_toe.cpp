// simple console tic-tac-toe game in C++
// choose a cell from 1 to 9 on your numpad to place your symbol
// if you dont have a numpad, the cells are arranged like this:
//  [7] [8] [9]
//  [4] [5] [6]
//  [1] [2] [3]

// include necessary libraries
#include <iostream>
#include <string>

// tic-tac-toe class definition
class tic_tac_toe
{
private:
	// 2d array to represent the tic-tac-toe board
	char board[3][3];

	// variable to keep track of the current player
	// true for player 1 (x), false for player 2 (o)
	bool player_turn = true;

	// define constants for the game states to avoid magic numbers
	static constexpr short player1_won = 1;
	static constexpr short player2_won = 2;
	static constexpr short tie = 3;
	static constexpr short continue_game = 0;

	// function to print the winning text if a player wins or if it's a draw
	void print_game_result(short winner)
	{
		print();
		if (winner == 1)
		{
			std::cout << "Player 1 (x) wins!" << std::endl;
		}
		else if (winner == 2)
		{
			std::cout << "Player 2 (o) wins!" << std::endl;
		}
		else
		{
			std::cout << "It's a draw!" << std::endl;
		}
	}

public:
	// constructor to initialize the tic-tac-toe board (add spaces to 2d array)
	tic_tac_toe()
	{
		for (short i = 0; i < 3; i++)
		{
			for (short j = 0; j < 3; j++)
			{
				board[i][j] = ' ';
			}
		}
	}

	// function to print the board
	// the board is printed upside down to match the numpad layout
	void print()
	{
		for (short i = 2; i >= 0; --i)
		{
			for (short j = 0; j < 3; j++)
			{
				std::cout << "[" << board[i][j] << "]";
			}
			std::cout << std::endl;
		}
	}

	// function to track the player's move
	void make_move()
	{

		// variables to keep track of the player's move
		std::string string_move;
		char move;

		// loop to keep prompting the player for a valid move
		while (true)
		{

			// prompt the player for their move
			if (player_turn)
			{
				std::cout << "Player 1 (x), enter your move: ";
			}
			else
			{
				std::cout << "Player 2 (o), enter your move: ";
			}

			// get the player's move
			std::getline(std::cin, string_move);

			// check if the input is valid
			if (string_move.length() != 1 || string_move[0] < '1' || string_move[0] > '9')
			{
				std::cout << "Invalid input. Please enter a single number between 1 and 9." << std::endl;
				continue;
			}

			// get the move as a char from the string
			move = string_move[0];

			// calculate the row and column based on the move
			int row = (move - '0' - 1) / 3;
			int col = (move - '0' - 1) % 3;

			// check to see if the cell is already occupied
			if (board[row][col] != ' ')
			{
				std::cout << "Cell already occupied. Please choose another cell." << std::endl;
				continue;

				// if the cell is empty, place the player's symbol in the cell and exit the loop
			}
			else
			{
				if (player_turn)
				{
					board[row][col] = 'x';
					player_turn = false;
				}
				else
				{
					board[row][col] = 'o';
					player_turn = true;
				}

				break;
			}
		}
	}

	// check for a winner
	short check_winner()
	{

		// check diagonals
		if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
		{
			if (board[0][0] == 'x')
			{
				print_game_result(player1_won);
				return player1_won;
			}
			else
			{
				print_game_result(player2_won);
				return player2_won;
			}
		}
		else if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
		{
			if (board[0][2] == 'x')
			{
				print_game_result(player1_won);
				return player1_won;
			}
			else
			{
				print_game_result(player2_won);
				return player2_won;
			}
		}

		// check rows and columns for a winner
		for (short i = 0; i < 3; i++)
		{

			// check rows
			if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
			{
				if (board[i][0] == 'x')
				{
					print_game_result(player1_won);
					return player1_won;
				}
				else
				{
					print_game_result(player2_won);
					return player2_won;
				}
			}

			// check columns
			if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
			{
				if (board[0][i] == 'x')
				{
					print_game_result(player1_won);
					return player1_won;
				}
				else
				{
					print_game_result(player2_won);
					return player2_won;
				}
			}
		}

		// if no winner and no empty cells, it's a draw
		for (short i = 0; i < 3; i++)
		{
			for (short j = 0; j < 3; j++)
			{
				if (board[i][j] == ' ')
				{
					return continue_game;
				}
			}
		}

		print_game_result(tie);
		return tie;
	}
};

// main function to start the game
int main()
{

	// create an instance of the tic_tac_toe class (object game)
	tic_tac_toe game;

	// start the game loop
	while (true)
	{

		// print the board
		game.print();

		// make a move
		game.make_move();

		// check for a winner
		short game_result = game.check_winner();

		// check the game result and handle accordingly
		switch (game_result)
		{
		case 0:
			continue;

		case 1:
		case 2:
		case 3:
			return 0;

		default:
			std::cout << "ERROR: Unexpected game state." << std::endl;
			return 1;
		}
	}

	return 0;
}