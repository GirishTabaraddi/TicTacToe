/*!
 * CGame.cpp
 *
 *  Created on: 01-Dec-2025
 *      Author: giris
 */

#include "CGame.h"
#include <cstdlib>
#include <iostream>

using namespace std;

CGame::CGame(unsigned int boardSize, EGameType gameType) :
		m_board(boardSize, boardSize)
{
	m_symbolInit(gameType);

	if (m_players[0]->getSymbol() == EBoardState::X)
	{
		m_currentPlayerIdx = 0;
	}
	else
	{
		m_currentPlayerIdx = 1;
	}

	m_isRunning = true;
}

CGame::~CGame()
{
	delete m_players[0];
	delete m_players[1];
}

unsigned int CGame::getCurrentPlayerIdx() const
{
	return m_currentPlayerIdx;
}

void CGame::m_symbolInit(EGameType gameType)
{
	unsigned int coinToss = rand() % 2;

	switch (gameType)
	{
	case EGameType::HvH:
		if (coinToss == 0)
		{
			m_players[0] = new CHuman(EBoardState::X);
			m_players[1] = new CHuman(EBoardState::O);
		}
		else
		{
			m_players[0] = new CHuman(EBoardState::O);
			m_players[1] = new CHuman(EBoardState::X);
		}
		break;
	case EGameType::HvC:
		if (coinToss == 0)
		{
			m_players[0] = new CHuman(EBoardState::X);
			m_players[1] = new CComputer(EBoardState::O);
		}
		else
		{
			m_players[0] = new CHuman(EBoardState::O);
			m_players[1] = new CComputer(EBoardState::X);
		}
		break;
	case EGameType::CvC:
		if (coinToss == 0)
		{
			m_players[0] = new CComputer(EBoardState::X);
			m_players[1] = new CComputer(EBoardState::O);
		}
		else
		{
			m_players[0] = new CComputer(EBoardState::O);
			m_players[1] = new CComputer(EBoardState::X);
		}
		break;
	default:
		break;
	}

}

void CGame::m_switchPlayer()
{
	if (m_currentPlayerIdx == 0)
		m_currentPlayerIdx = 1;
	else
		m_currentPlayerIdx = 0;
}

void CGame::m_checkResult()
{
	EGameResult resultStatus = m_board.checkWinStatus();

	switch (resultStatus)
	{
	case EGameResult::X_WINS:
		m_display.printBoard(m_board);
		cout << "Player X Wins!!!" << endl;
		m_isRunning = false;
		break;
	case EGameResult::O_WINS:
		m_display.printBoard(m_board);
		cout << "Player O Wins!!!" << endl;
		m_isRunning = false;
		break;
	case EGameResult::DRAW:
		m_display.printBoard(m_board);
		cout << "Unfortunately it is a draw!!!" << endl;
		m_isRunning = false;
		break;
	default:
		//! Game is still playing, do nothing
		break;
	}
}

void CGame::playGame()
{
	while (m_isRunning)
	{
		m_display.printBoard(m_board);

		CPlayer *currentPlayer = m_players[m_currentPlayerIdx];

		cout << endl << "Player " << currentPlayer->getSymbol() <<
				" (" << currentPlayer->getPlayerType() << ") turn:" << endl << endl;

		Coordinates currentPlayerCoordinates = currentPlayer->decideMove(
				m_board);

		m_board.setCellValue(currentPlayerCoordinates.row,
				currentPlayerCoordinates.col, currentPlayer->getSymbol());

		m_checkResult();

		if (m_isRunning)
		{
			m_switchPlayer();
		}
	}
}

void CGame::printPlayerInfo() const
{
	for (unsigned int i = 0; i < 2; i++)
	{
		cout << endl << "Player " << i << ": " << m_players[i]->getPlayerType()
				<< " (" << m_players[i]->getSymbol() << ")"
				<< endl;
	}
}
