//! Standard (system) header files
#include <iostream>
#include <cstdlib>
//! Add more standard header files as required

using namespace std;

//! Add your project's header files here
#include "CGame.h"

void startTicTacToe();

int main ()
{
	startTicTacToe();

	return 0;
}

void startTicTacToe()
{
	cout << "TicTacToe started." << endl << endl;

	unsigned int boardSize = 3;

	unsigned int temp_gameType = 0;

	EGameType gameType = EGameType::CvC;

	CGame* game	=	nullptr;

	bool isGameTypeValid = false;

	while(isGameTypeValid == false)
	{
		cout << "Choose the Game Type from below options: " << endl
				<< "1. Human vs Human" << endl
				<< "2. Human vs Computer" << endl
				<< "3. Computer vs Computer" << endl;

		cin >> temp_gameType;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid input. Please enter a number." << endl << endl;
			continue;
		}

		if(temp_gameType < 1 || temp_gameType > 3)
		{
			cout << "Please enter a valid option (1-3)!" << endl << endl;
			continue;
		}

		switch(temp_gameType)
		{
		case 1:
			gameType = EGameType::HvH;
			break;
		case 2:
			gameType = EGameType::HvC;
			break;
		case 3:
			gameType = EGameType::CvC;
			break;
		default:
			gameType = EGameType::CvC;
		}

		isGameTypeValid = true;
	}

	while(game == nullptr)
	{

		cout << "Enter TicTacToe Board Size (3, 4, or 5): ";

		cin >> boardSize;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid input. Please enter a number for board size." << endl << endl;
			continue;
		}

		try
		{
			game = new CGame(boardSize, gameType);
		}
		catch(const invalid_argument& e)
		{
			cout << "Error: " << e.what() << endl;
			cout << "Please enter a valid size for the board!!!" << endl << endl;
		}
	}

	cout << endl << "----------- Game Configuration -----------" << endl << endl;
	cout << "Type: ";
	switch(gameType) {
		case EGameType::HvH: cout << "Human vs Human" << endl; break;
		case EGameType::HvC: cout << "Human vs Computer" << endl; break;
		case EGameType::CvC: cout << "Computer vs Computer" << endl; break;
	}
	cout << endl << "Grid: " << boardSize << "x" << boardSize << endl;
	game->printPlayerInfo();
	cout << "---------------------------------------" << endl << endl;

	if(game != nullptr)
	{
		game->playGame();

		delete game;

		game = nullptr;
	}

	cout << endl << "Game Ended!!!" << endl;
}
