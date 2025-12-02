/*!
 * CComputer.h
 *
 *  Created on: 1 Dec 2025
 *      Author: GTABARA
 */

#ifndef CCOMPUTER_H_
#define CCOMPUTER_H_

#include "CPlayer.h"

class CComputer: public CPlayer
{
public:
	CComputer(EBoardState symbol);
	virtual ~CComputer();
	virtual Coordinates decideMove(const CBoard &board) override;
	virtual std::string getPlayerType() const override;

private:
	int m_findOptimalCellValue(CBoard& board, unsigned int depth, bool checkTurn);

	EBoardState getOpponentSymbol() const;
};

#endif /* CCOMPUTER_H_ */
