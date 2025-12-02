/*!
 * CDisplay.h
 *
 *  Created on: 29-Nov-2025
 *      Author: giris
 */

#ifndef CDISPLAY_H_
#define CDISPLAY_H_

#include "GameTypes.h"

//! Forward declaration allows CDisplay to compile without the full CBoard definition.
class CBoard;

/*!
 * @class CDisplay
 * @brief The "View" class responsible for rendering game information to the console.
 * * This class handles all standard output operations, including drawing the
 * game board, player prompts, and game result messages.
 */
class CDisplay
{
public:
    /*!
     * @brief Default Constructor.
     */
    CDisplay();

    /*!
     * @brief Virtual Destructor.
     */
    virtual ~CDisplay();

    /*!
     * @brief Renders the current state of the board to the standard output.
     * * This function iterates through the CBoard object and prints the
     * corresponding symbols (X, O, or .) in a grid format.
     * * @param board A constant reference to the Board object.
     * The board is passed as const to ensure the display
     * cannot modify game data.
     */
    void printBoard(const CBoard& board) const;
};

#endif /* CDISPLAY_H_ */
