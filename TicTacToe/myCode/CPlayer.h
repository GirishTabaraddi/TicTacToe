/*!
 * CPlayer.h
 *
 *  Created on: 30-Nov-2025
 *      Author: giris
 */

#ifndef CPLAYER_H_
#define CPLAYER_H_

#include "GameTypes.h"

class CBoard;

struct Coordinates
{
	unsigned int row;
	unsigned int col;
};

class CPlayer
{
protected:
	EBoardState m_symbol;

public:
	CPlayer(EBoardState symbol);
	virtual ~CPlayer();

	virtual Coordinates decideMove(const CBoard& board) = 0;

	EBoardState getSymbol() const;

	virtual std::string getPlayerType() const = 0;
};

#endif /* CPLAYER_H_ */
