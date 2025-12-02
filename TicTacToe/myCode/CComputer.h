/*!
 * CComputer.h
 *
 *  Created on: 1 Dec 2025
 *      Author: GTABARA
 */

#ifndef CCOMPUTER_H_
#define CCOMPUTER_H_

#include "CPlayer.h"

/*!
 * @class CComputer
 * @brief Represents an Smart Computer player in the Tic-Tac-Toe game.
 * * This class uses the algorithm of calculating optimal moves for 3x3 boards to play smartly
 * and falls back to random selection for larger boards to save computation time.
 */
class CComputer: public CPlayer
{
public:
    /*!
     * @brief Constructs a Computer player.
     * @param symbol The symbol (X or O) assigned to this Computer.
     */
    CComputer(EBoardState symbol);

    /*!
     * @brief Virtual destructor.
     */
    virtual ~CComputer();

    /*!
     * @brief Calculates the best move for the Computer.
     * * If Board Size == 3x3: Uses algorithm.
     * If Board Size > 3x3: Uses Random selection.
     * * @param board Reference to the current game board.
     * @return Coordinates The calculated optimal (or random) move.
     */
    virtual Coordinates decideMove(const CBoard &board) override;

    /*!
     * @brief Returns the description of the player type.
     * @return std::string "Computer"
     */
    virtual std::string getPlayerType() const override;

private:
    /*!
     * @brief Recursive algorithm to find the best score for a move.
     * * Simulates all possible future moves to determine the outcome.
     * Returns +10 for Computer win, -10 for Opponent win, 0 for Draw.
     * Adjusts score based on 'depth' to prefer winning sooner rather than later.
     * * @param board The board state being simulated.
     * @param depth The current depth of recursion (number of moves ahead).
     * @param checkTurn Boolean flag: true if Maximizing (Computer turn), false if Minimizing (Opponent turn).
     * @return int The calculated score of the board state.
     */
    int m_findOptimalCellValue(CBoard& board, unsigned int depth, bool checkTurn);

    /*!
     * @brief Helper to determine the opponent's symbol.
     * * Used during simulation to place the opponent's pieces.
     * @return EBoardState Returns O if Computer is X, or X if Computer is O.
     */
    EBoardState getOpponentSymbol() const;
};

#endif /* CCOMPUTER_H_ */
