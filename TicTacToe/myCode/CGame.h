/*!
 * CGame.h
 *
 *  Created on: 01-Dec-2025
 *      Author: giris
 */

#ifndef CGAME_H_
#define CGAME_H_

#include "CBoard.h"
#include "CDisplay.h"
#include "CHuman.h"
#include "CComputer.h"

class CGame
{
private:
	CBoard m_board;
	CDisplay m_display;
	CPlayer* m_players[2];
	unsigned int m_currentPlayerIdx;
	bool m_isRunning;

public:
	CGame(unsigned int boardSize, EGameType gameType);
	virtual ~CGame();

	void playGame();

	unsigned int getCurrentPlayerIdx() const;

	void printPlayerInfo() const;

private:
	void m_switchPlayer();

	void m_symbolInit(EGameType gameType);

	void m_checkResult();
};

#endif /* CGAME_H_ */
