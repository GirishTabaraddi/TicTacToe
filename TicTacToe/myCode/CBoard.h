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

/*!
 * @class CBoard
 * @brief Represents the Tic-Tac-Toe game board data and logic.
 *
 * This class manages the internal 1D vector representation of the 2D grid,
 * handles coordinate validation, and implements the algorithms to detect
 * win conditions (Rows, Columns, and Diagonals).
 */
class CBoard
{
private:
	/*!< The number of rows in the grid (e.g., 3, 4, or 5). */
	unsigned int m_rows;

	/*!< The number of columns in the grid. */
	unsigned int m_cols;

	/*!
	 * @brief The internal data structure for the grid.
	 * @details A 1D vector representing the 2D board.
	 * Mapping formula: Index = (Row * m_cols) + Col.
	 */
	std::vector<EBoardState> m_board;

public:
	/*!
	 * @brief Parameterized Constructor.
	 * * Initializes the board dimensions and allocates the vector memory
	 * initialized to EBoardState::EMPTY.
	 *
	 * @param rows The number of rows (must be between 3 and 5).
	 * @param cols The number of columns (must equal rows).
	 * @throws std::invalid_argument If dimensions are unequal or out of range.
	 */
	CBoard(unsigned int rows, unsigned cols);

	/*!
	 * @brief Destructor.
	 * * Handles clean-up of the CBoard object.
	 * * std::vector manages its own memory automatically.
	 */
	virtual ~CBoard();

	/*!
	 * @brief Getter for the number of rows.
	 * @return The unsigned integer representing total rows.
	 */
	unsigned int getRows() const;

	/*!
	 * @brief Getter for the number of columns.
	 * @return The unsigned integer representing total columns.
	 */
	unsigned int getCols() const;

	/*!
	 * @brief Retrieves the state of a specific cell.
	 * * Converts the 2D (row, col) coordinates into the 1D vector index
	 * to fetch the data.
	 *
	 * @param row The row index (0-based).
	 * @param col The column index (0-based).
	 * @return The state of the cell (EMPTY, X, or O).
	 */
	EBoardState getCellValue(unsigned int row, unsigned int col) const;

	/*!
	 * @brief Places a move on the board.
	 * * Updates the internal vector with the player's move.
	 *
	 * @param row The target row index.
	 * @param col The target column index.
	 * @param value The symbol to place (X or O).
	 * @throws std::invalid_argument If the target cell is not EMPTY.
	 */
	void setCellValue(unsigned int row, unsigned int col, EBoardState value);

	/*!
	 * @brief Clears a specific cell back to EMPTY.
	 * * This is primarily used by the CComputer to "undo"
	 * temporary moves during calculation.
	 *
	 * @param row The row index to reset.
	 * @param col The column index to reset.
	 */
	void resetCellValue(unsigned int row, unsigned int col);

	/*!
	 * @brief Analyzes the board for a winner or draw.
	 * * Aggregates results from row, column, and diagonal checks.
	 *
	 * @return EGameResult::X_WINS, O_WINS, DRAW, or PLAYING.
	 */
	EGameResult checkWinStatus();

private:
	/*!
	 * @brief Helper function to check all rows for a winning line.
	 * @return The result if a row win is found, otherwise PLAYING.
	 */
	EGameResult checkAllRows();

	/*!
	 * @brief Helper function to check all columns for a winning line.
	 * @return The result if a column win is found, otherwise PLAYING.
	 */
	EGameResult checkAllCols();

	/*!
	 * @brief Helper function to check both Main and Anti diagonals.
	 * @return The result if a diagonal win is found, otherwise PLAYING.
	 */
	EGameResult checkAllDiagonals();
};

#endif /* CBOARD_H_ */
