/*!
 * CHuman.cpp
 *
 *  Created on: 30-Nov-2025
 *      Author: giris
 */

#include "CHuman.h"
#include "CBoard.h"
#include <iostream>

using namespace std;

CHuman::CHuman(EBoardState symbol) : CPlayer(symbol)
{
}

CHuman::~CHuman()
{
}

Coordinates CHuman::decideMove(const CBoard &board)
{
	unsigned int inputRow = 0;
	unsigned int inputCol = 0;

	Coordinates tempCoordinates;

	bool isOccupied;
	bool isOutOfBounds;

	do
	{
		isOccupied = false;
		isOutOfBounds = false;

		cout << endl << "Enter row value (1-" << board.getRows() << "): ";
		cin >> inputRow;

		if(cin.fail())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Error: Please enter a number." << endl;

			isOutOfBounds = true;
			continue;
		}

		cout << endl << "Enter row value (1-" << board.getCols() << "): ";
		cin >> inputCol;

		if(cin.fail())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Error: Please enter a number." << endl;

			isOutOfBounds = true;
			continue;
		}

		if(inputRow < 1 || inputRow > board.getRows()
				|| inputCol < 1 || inputCol >= board.getCols())
		{
			isOutOfBounds = true;
			cout << "Error: Out of bounds." << endl;
			continue;
		}
		else if(board.getCellValue(inputRow-1, inputCol-1) != EBoardState::EMPTY)
		{
			isOccupied = true;
			cout << "Error: Spot taken." << endl;
			continue;
		}
	}while(isOutOfBounds || isOccupied);


	tempCoordinates.row = inputRow - 1;
	tempCoordinates.col = inputCol - 1;

	return tempCoordinates;
}
