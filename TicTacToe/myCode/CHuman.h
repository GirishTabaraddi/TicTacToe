/*!
 * CHuman.h
 *
 *  Created on: 30-Nov-2025
 *      Author: giris
 */

#ifndef CHUMAN_H_
#define CHUMAN_H_

#include "CPlayer.h"

/**
 * @class CHuman
 * @brief Represents a human player in the Tic-Tac-Toe game.
 * * This class handles interaction with the user via the console, asking for
 * row and column inputs to determine the next move.
 */
class CHuman: public CPlayer
{
public:
    /**
     * @brief Constructs a Human player.
     * @param symbol The symbol (X or O) assigned to this player.
     */
    CHuman(EBoardState symbol);

    /**
     * @brief Virtual destructor to ensure proper cleanup of derived resources.
     */
    virtual ~CHuman();

    /**
     * @brief Prompts the user via console to select a move.
     * * Handles input validation (checking for non-numbers) and logic validation
     * (checking boundaries and checking if the cell is already occupied).
     * * @param board Reference to the current game board (used for validation).
     * @return Coordinates The valid row and column selected by the user.
     */
    virtual Coordinates decideMove(const CBoard &board) override;

    /**
     * @brief Returns the description of the player type.
     * @return std::string "Human"
     */
    virtual std::string getPlayerType() const override;
};

#endif /* CHUMAN_H_ */
