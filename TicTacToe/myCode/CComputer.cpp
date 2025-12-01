/*
 * CComputer.cpp
 *
 *  Created on: 1 Dec 2025
 *      Author: GTABARA
 */

#include "CComputer.h"
#include "CBoard.h"
#include <iostream>
#include <cstdlib>

using namespace std;

CComputer::~CComputer()
{
}

CComputer::CComputer(EBoardState symbol) : CPlayer(symbol)
{
}

Coordinates CComputer::decideMove(const CBoard &board)
{
	unsigned int tempRow = 0;
	unsigned int tempCol = 0;

	Coordinates tempCoordinates;

	bool isOccupied;

	tempRow = rand() % board.getRows();
	tempCol = rand() % board.getRows();

	do
	{
		isOccupied = false;

		if(board.getCellValue(tempRow, tempCol) != EBoardState::EMPTY)
		{
			isOccupied = true;
			continue;
		}
	}while(isOccupied);

	tempCoordinates.row = tempRow;
	tempCoordinates.col = tempCol;

	return tempCoordinates;
}
