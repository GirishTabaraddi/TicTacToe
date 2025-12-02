/*!
 * CPlayer.h
 *
 *  Created on: 30-Nov-2025
 *      Author: giris
 */

#ifndef CPLAYER_H_
#define CPLAYER_H_

#include "GameTypes.h"

//! Forward declaration for CPlayer usage
class CBoard;

/*!
 * @struct Coordinates
 * @brief A structure to transport row and column indices.
 * * Used primarily as the return type for player move decisions.
 */
struct Coordinates
{
    /// @brief The row index (0-based).
    unsigned int row;

    /// @brief The column index (0-based).
    unsigned int col;
};

/*!
 * @class CPlayer
 * @brief Abstract Base Class representing a participant in the game.
 * * This class defines the interface for any entity that can play Tic-Tac-Toe,
 * whether it is a Human or a Computer. It implements the Strategy Pattern
 * via the pure virtual function decideMove().
 */
class CPlayer
{
protected:
    /*!
     * @brief Stores the symbol assigned to this player.
     * Protected visibility allows derived classes (CHuman/CComputer)
     * to access it if necessary for logic checks.
     */
    EBoardState m_symbol;

public:
    /*!
     * @brief Constructor.
     * @param symbol The specific token (X or O) this player will use throughout the game.
     */
    CPlayer(EBoardState symbol);

    /*!
     * @brief Virtual Destructor.
     * Essential for Dynamic Polymorphism to ensure the derived class
     * destructor is called when deleting a CPlayer pointer.
     */
    virtual ~CPlayer();

    /*!
     * @brief Calculates or retrieves the coordinates for the next move.
     * * This is a Pure Virtual Function that must be implemented by derived classes.
     * - For CHuman: It prompts the user for input via cin.
     * - For CComputer: It calculates the best move via simulating the moves or Random logic.
     * * @param board The current state of the game board, used for validation
     * and decision making.
     * @return Coordinates A struct containing the target [row, col].
     */
    virtual Coordinates decideMove(const CBoard& board) = 0;

    /*!
     * @brief Accessor for the player's assigned symbol.
     * @return EBoardState The enum value (X or O) belonging to this player.
     */
    EBoardState getSymbol() const;

    /*!
     * @brief Identifies the type of player for UI display.
     * @return std::string A textual description (e.g., "Human" or "Computer").
     */
    virtual std::string getPlayerType() const = 0;
};

#endif /* CPLAYER_H_ */
