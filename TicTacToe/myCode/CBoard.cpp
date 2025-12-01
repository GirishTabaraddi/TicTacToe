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
	if (rows == cols && rows > 2 && rows < 6 && cols > 2 && cols < 6)
	{
		m_rows = rows;
		m_cols = cols;

		m_board.assign(rows * cols, EBoardState::EMPTY);
	}
	else
	{
		throw invalid_argument("Only 3x3, 4x4, or 5x5 boards allowed.");
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

void CBoard::setCellValue(unsigned int row, unsigned int col, EBoardState value)
{
	if (getCellValue(row, col) == EBoardState::EMPTY)
	{
		unsigned int idx = (row * m_cols) + col;

		m_board[idx] = value;
	}
	else
	{
		throw invalid_argument("The entered (row, col) cell is occupied.");
	}
}

EGameResult CBoard::checkWinStatus()
{
	EGameResult rowResult = checkAllRows();
	if(rowResult != EGameResult::PLAYING) return rowResult;

	EGameResult colResult = checkAllCols();
	if(colResult != EGameResult::PLAYING) return colResult;

	EGameResult diagResult = checkAllDiagonals();
	if(diagResult != EGameResult::PLAYING) return diagResult;

	for(unsigned int idx = 0; idx < m_board.size(); idx++)
	{
			if(m_board[idx] == EBoardState::EMPTY) return EGameResult::PLAYING;
	}

	return EGameResult::DRAW;
}

EGameResult CBoard::checkAllRows()
{
	EGameResult rowResult = EGameResult::PLAYING;

	for (unsigned int rIdx = 0; rIdx < m_rows; rIdx++)
	{
		EBoardState firstCell = m_board[rIdx * m_rows];

		if(firstCell == EBoardState::EMPTY) continue;

		bool mismatchFoundFlag = false;

		for (unsigned int cIdx = 0; cIdx < m_cols; cIdx++)
		{
			unsigned int cellIdx = (rIdx * m_cols) + cIdx;

			if (firstCell != m_board[cellIdx])
			{
				mismatchFoundFlag = true;
				break;
			}
		}

		if(!mismatchFoundFlag)
		{
			if(firstCell == EBoardState::X) rowResult = EGameResult::X_WINS;
			else rowResult = EGameResult::O_WINS;
		}

	}

	return rowResult;
}

EGameResult CBoard::checkAllCols()
{
	EGameResult colResult = EGameResult::PLAYING;

	for (unsigned int cIdx = 0; cIdx < m_cols; cIdx++)
	{
		EBoardState firstCell = m_board[cIdx * m_cols];

		if(firstCell == EBoardState::EMPTY) continue;

		bool mismatchFoundFlag = false;

		for (unsigned int rIdx = 0; rIdx < m_rows; rIdx++)
		{
			unsigned int cellIdx = (rIdx * m_cols) + cIdx;

			if (firstCell != m_board[cellIdx])
			{
				mismatchFoundFlag = true;
				break;
			}
		}

		if(!mismatchFoundFlag)
		{
			if(firstCell == EBoardState::X) colResult = EGameResult::X_WINS;
			else colResult = EGameResult::O_WINS;
		}
	}

	return colResult;
}

EGameResult CBoard::checkAllDiagonals()
{
	EGameResult diagResult = EGameResult::PLAYING;

	EBoardState leftDiagCell = m_board[0];

	if(leftDiagCell != EBoardState::EMPTY)
	{
		bool mismatchFoundFlag = false;

		for(unsigned int i = 1; i < m_rows; i++)
		{
			unsigned int leftDiagIdx = (i * m_cols) + i;

			if(leftDiagCell != m_board[leftDiagIdx])
			{
				mismatchFoundFlag = true;
				break;
			}
		}

		if(!mismatchFoundFlag)
		{
			if(leftDiagCell == EBoardState::X) diagResult = EGameResult::X_WINS;
			else diagResult = EGameResult::O_WINS;
		}
	}

	EBoardState rightDiagCell = m_board[m_cols - 1];

	if(rightDiagCell != EBoardState::EMPTY)
	{
		bool mismatchFoundFlag = false;

		for(unsigned int i = 1; i < m_rows; i++)
		{
			unsigned int rightDiagIdx = (i * m_cols) + ((m_cols - 1) - i);

			if(rightDiagCell != m_board[rightDiagIdx])
			{
				mismatchFoundFlag = true;
				break;
			}
		}

		if(!mismatchFoundFlag)
		{
			if(rightDiagCell == EBoardState::X) diagResult = EGameResult::X_WINS;
			else diagResult = EGameResult::O_WINS;
		}
	}

	return diagResult;
}
