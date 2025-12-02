/*!
 * CHuman.h
 *
 *  Created on: 30-Nov-2025
 *      Author: giris
 */

#ifndef CHUMAN_H_
#define CHUMAN_H_

#include "CPlayer.h"

class CHuman: public CPlayer
{
public:
	CHuman(EBoardState symbol);
	virtual ~CHuman();
	virtual Coordinates decideMove(const CBoard &board) override;
	virtual std::string getPlayerType() const override;
};

#endif /* CHUMAN_H_ */
