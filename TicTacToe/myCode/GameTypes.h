/*!
 * GameTypes.h
 *
 *  Created on: 29-Nov-2025
 *      Author: giris
 */

#ifndef GAMETYPES_H_
#define GAMETYPES_H_

#include <cctype>
#include <iostream>

/**
 * @brief Represents the state of a single cell on the Tic-Tac-Toe board.
 * * This enum class inherits from char to facilitate easy printing to the console.
 */
enum class EBoardState : char
{
    /// @brief Represents an unoccupied cell (displayed as '.')
    EMPTY   =   '.',
    /// @brief Represents Player X (displayed as 'x')
    X       =   'x',
    /// @brief Represents Player O (displayed as 'o')
    O       =   'o'
};

/**
 * @brief Utility function to normalize board symbols to lowercase.
 * * This ensures that if a user or system passes uppercase 'X' or 'O',
 * it is correctly converted to the standard EBoardState values.
 * * @param symbol The input board state/character to convert.
 * @return EBoardState The normalized lowercase state (X, O, or EMPTY).
 */
inline EBoardState toLowerCase(EBoardState symbol)
{
    char temp_symbol = static_cast<char>(symbol);

    temp_symbol = static_cast<char>(tolower(temp_symbol));

    if(temp_symbol == 'x') return EBoardState::X;
    else if(temp_symbol == 'o') return EBoardState::O;
    else return EBoardState::EMPTY;
}

/**
 * @brief Defines the available game modes.
 */
enum class EGameType
{
    /// @brief Human vs Human (Hotseat mode).
    HvH,
    /// @brief Human vs Computer (Player vs Computer).
    HvC,
    /// @brief Computer vs Computer (Computer vs Computer).
    CvC
};

/**
 * @brief Represents the current status or final result of the game.
 */
enum class EGameResult
{
    /// @brief The game is currently in progress.
    PLAYING,
    /// @brief Player X has won the game.
    X_WINS,
    /// @brief Player O has won the game.
    O_WINS,
    /// @brief The board is full and no winner was declared.
    DRAW
};

/**
 * @brief Overloaded stream insertion operator for EBoardState.
 * * Allows direct printing of enum values to streams (e.g., cout << EBoardState::X).
 * * @param lhs The output stream (e.g., std::cout).
 * @param state The board state to print.
 * @return std::ostream& Reference to the modified output stream.
 */
inline std::ostream& operator<<(std::ostream& lhs, const EBoardState& state)
{
    switch(state)
    {
    case EBoardState::EMPTY:
        lhs << '.';
        break;
    case EBoardState::X:
        lhs << 'x';
        break;
    case EBoardState::O:
        lhs << 'o';
        break;
    default:
        lhs << '?';
        break;
    }

    return lhs;
}

#endif /* GAMETYPES_H_ */
