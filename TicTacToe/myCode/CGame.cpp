/*!
 * CGame.cpp
 *
 *  Created on: 01-Dec-2025
 *      Author: giris
 */

#include "CGame.h"
#include <cstdlib>

using namespace std;

CGame::CGame(unsigned int boardSize, EGameType gameType):m_board(boardSize, boardSize)
{
	m_symbolInit(gameType);

	if(m_players[0]->getSymbol() == EBoardState::X)
	{
		m_currentPlayerIdx	=	0;
	}
	else
	{
		m_currentPlayerIdx	=	1;
	}

	m_isRunning	=	true;
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

	switch(gameType)
	{
	case EGameType::HvH:
		if(coinToss == 0)
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
		if(coinToss == 0)
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
		if(coinToss == 0)
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

void CGame::playGame()
{
}

void CGame::m_switchPlayer()
{
}


