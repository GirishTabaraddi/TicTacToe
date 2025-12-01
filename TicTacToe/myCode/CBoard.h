/*!
 * CBoard.h
 *
 *  Created on: 29-Nov-2025
 *      Author: giris
 */

#ifndef CBOARD_H_
#define CBOARD_H_

#include <vector>
#include "GameTypes.h"

class CBoard
{
private:
	/*! rows of the TicTacToe board */
	unsigned int m_rows;

	/*! rows of the TicTacToe board */
	unsigned int m_cols;

	/*! the board that stores rows & columns in a 1D vector */
	std::vector<EBoardState> m_board;

public:
	/*! Parameterized constructor for the CBoard class that initializes the rows and the columns
	 *  Also allocates memory for the board */
	CBoard(unsigned int rows, unsigned cols);

	/*! Destructor for the class member m_board which has memory allocated in heap */
	virtual ~CBoard();

	unsigned int getRows() const;

	unsigned int getCols() const;

	EBoardState getCellValue(unsigned int row, unsigned int col) const;

	void setCellValue(unsigned int row, unsigned int col, EBoardState value);

	EGameResult checkWinStatus();

private:
	EGameResult checkAllRows();
	EGameResult checkAllCols();
	EGameResult checkAllDiagonals();
};

#endif /* CBOARD_H_ */
