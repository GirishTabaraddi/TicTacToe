/*!
 * CBoard.cpp
 *
 *  Created on: 29-Nov-2025
 *      Author: giris
 */

#include "CBoard.h"
#include <stdexcept>

using namespace std;

CBoard::CBoard(unsigned int rows, unsigned cols)
{
	if(rows == cols && rows > 2 && rows < 6 && cols > 2 && cols < 6)
	{
		m_rows	=	rows;
		m_cols	=	cols;

		m_board.assign(rows * cols, EBoardState::EMPTY);
	}
	else
	{
		throw std::invalid_argument("Only 3x3, 4x4, or 5x5 boards allowed.");
	}
}

CBoard::~CBoard()
{
}

unsigned int CBoard::getRows() const
{
	return m_rows;
}

unsigned int CBoard::getCols() const
{
	return m_cols;
}

EBoardState CBoard::getCellValue(unsigned int row, unsigned int col) const
{
	return m_board[(row * m_cols) + col];
}
