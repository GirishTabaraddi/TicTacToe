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
	if(board.getRows() == 3)
	{
		Coordinates bestMove = {0,0};

		int bestScore = -1000;

		CBoard tempBoard = board;

		for(unsigned int rIdx = 0; rIdx < tempBoard.getRows(); rIdx++)
		{
			for(unsigned int cIdx = 0; cIdx < tempBoard.getCols(); cIdx++)
			{
				if(tempBoard.getCellValue(rIdx, cIdx) == EBoardState::EMPTY)
				{
					tempBoard.setCellValue(rIdx, cIdx, getSymbol());

					int score = m_findOptimalCellValue(tempBoard, 0, false);

					tempBoard.resetCellValue(rIdx, cIdx);

					if(score > bestScore)
					{
						bestScore = score;
						bestMove.row = rIdx;
						bestMove.col = cIdx;
					}
				}
			}
		}
		return bestMove;
	}
	else
	{
		unsigned int tempRow = 0;
		unsigned int tempCol = 0;

		Coordinates tempCoordinates;

		bool isOccupied = false;

		do
		{
			tempRow = rand() % board.getRows();
			tempCol = rand() % board.getCols();

			if(board.getCellValue(tempRow, tempCol) != EBoardState::EMPTY)
			{
				isOccupied = true;
				continue;
			}
			else isOccupied = false;
		}while(isOccupied);

		tempCoordinates.row = tempRow;
		tempCoordinates.col = tempCol;

		return tempCoordinates;
	}
}

std::string CComputer::getPlayerType() const
{
	return "Computer";
}

int CComputer::m_findOptimalCellValue(CBoard &board,
		unsigned int depth, bool checkTurn)
{
	EGameResult result = board.checkWinStatus();

	if(result != EGameResult::PLAYING)
	{
		if(result == EGameResult::DRAW)
		{
			return 0;
		}

		if((result == EGameResult::X_WINS && getSymbol() == EBoardState::X) ||
				(result == EGameResult::O_WINS && getSymbol() == EBoardState::O))
		{
			return 10 - depth;
		}
		else
		{
			return -10 + depth;
		}
	}

	if(checkTurn)
	{
		int bestScore = -1000;

		for(unsigned int rIdx = 0; rIdx < board.getRows(); rIdx++)
		{
			for(unsigned int cIdx = 0; cIdx < board.getCols(); cIdx++)
			{
				if(board.getCellValue(rIdx, cIdx) == EBoardState::EMPTY)
				{
					board.setCellValue(rIdx, cIdx, getSymbol());

					int score = m_findOptimalCellValue(board, depth + 1, false);

					board.resetCellValue(rIdx, cIdx);

					if(score > bestScore) bestScore = score;
				}
			}
		}
		return bestScore;
	}
	else
	{
		int bestScore = 1000;

		for(unsigned int rIdx = 0; rIdx < board.getRows(); rIdx++)
		{
			for(unsigned int cIdx = 0; cIdx < board.getCols(); cIdx++)
			{
				if(board.getCellValue(rIdx, cIdx) == EBoardState::EMPTY)
				{
					board.setCellValue(rIdx, cIdx, getOpponentSymbol());

					int score = m_findOptimalCellValue(board, depth + 1, true);

					board.resetCellValue(rIdx, cIdx);

					if(score < bestScore) bestScore = score;
				}
			}
		}
		return bestScore;
	}
}

EBoardState CComputer::getOpponentSymbol() const
{
	if(getSymbol() == EBoardState::O) return EBoardState::X;
	else return EBoardState::O;
}
