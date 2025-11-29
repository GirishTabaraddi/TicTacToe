/*!
 * CDisplay.cpp
 *
 *  Created on: 29-Nov-2025
 *      Author: giris
 */

#include "CDisplay.h"

#include "CBoard.h"

#include <iostream>

using namespace std;

CDisplay::CDisplay()
{
}

CDisplay::~CDisplay()
{
}

void CDisplay::printBoard(const CBoard &board) const
{
	unsigned int rows = board.getRows();

	unsigned int cols = board.getCols();

	for(unsigned int r_idx = 0; r_idx < rows; r_idx++)
	{
		for(unsigned int c_idx = 0; c_idx < cols; c_idx++)
		{
			EBoardState state = board.getCellValue(r_idx, c_idx);

			switch(state)
			{
			case(EBoardState::X):
					cout << 'x' << ' ';
			break;
			case(EBoardState::O):
					cout << 'o' << ' ';
			break;
			default:
				cout << '.' << ' ';
			}
		}
		cout << endl;
	}
}
