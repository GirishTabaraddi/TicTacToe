/*!
 * CPlayer.cpp
 *
 *  Created on: 30-Nov-2025
 *      Author: giris
 */

#include "CPlayer.h"
#include "CBoard.h"
#include <iostream>
#include <stdexcept>

using namespace std;

CPlayer::CPlayer(EBoardState symbol)
{
	EBoardState temp_symbol	=	toLowerCase(symbol);

	if(temp_symbol == EBoardState::X || temp_symbol == EBoardState::O)
	{
		m_symbol	=	temp_symbol;
	}
	else
	{
		throw invalid_argument("The symbol can only be smallcase 'x' or 'o'");
	}
}

CPlayer::~CPlayer()
{

}

EBoardState CPlayer::getSymbol() const
{
	return m_symbol;
}
