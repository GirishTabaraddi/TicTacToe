/*!
 * GameTypes.h
 *
 *  Created on: 29-Nov-2025
 *      Author: giris
 */

#ifndef GAMETYPES_H_
#define GAMETYPES_H_

#include <cctype>

enum class EBoardState : char
{
	EMPTY	=	'.',
	X		=	'x',
	O		=	'o'
};

inline EBoardState toLowerCase(EBoardState symbol)
{
	char temp_symbol = static_cast<char>(symbol);

	temp_symbol = static_cast<char>(tolower(temp_symbol));

	if(temp_symbol == 'x') return EBoardState::X;
	else if(temp_symbol == 'o') return EBoardState::O;
	else return EBoardState::EMPTY;
}

enum class EGameType
{
	HvH,
	HvC,
	CvC
};

enum class EGameResult
{
	PLAYING,
	X_WINS,
	O_WINS,
	DRAW
};

#endif /* GAMETYPES_H_ */
