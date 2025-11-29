/*!
 * CBoard.cpp
 *
 *  Created on: 29-Nov-2025
 *      Author: giris
 */

#include "CBoard.h"

#include <iostream>

using namespace std;

CBoard::CBoard(unsigned int rows, unsigned cols)
{
	m_rows	=	rows;
	m_cols	=	cols;

	m_board.assign(rows * cols, EBoardState::EMPTY);
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
