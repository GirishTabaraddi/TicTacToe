/*!
 * CDisplay.h
 *
 *  Created on: 29-Nov-2025
 *      Author: giris
 */

#ifndef CDISPLAY_H_
#define CDISPLAY_H_

#include "GameTypes.h"

/*! Forward declaration of CBoard class, as CDisplay need to only
 *  know that CBoard exists, it doesn't need to initialize it.*/
class CBoard;

class CDisplay
{
public:
	CDisplay();
	virtual ~CDisplay();

	void printBoard(const CBoard& board) const;
};

#endif /* CDISPLAY_H_ */
