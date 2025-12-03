/*!
 * CGame.h
 *
 *  Created on: 01-Dec-2025
 *      Author: giris
 */

#ifndef CGAME_H_
#define CGAME_H_

#include "CBoard.h"
#include "CDisplay.h"
#include "CHuman.h"
#include "CComputer.h"

/*!
 * @class CGame
 * @brief The Controller class for the Tic-Tac-Toe application.
 *
 * This class acts as the central engine (Controller in MVC). It manages the
 * lifecycle of the game, including the Board (Model), the Display (View),
 * and the Players. It controls the game loop, turn switching, and result checking.
 */
class CGame
{
    friend class WasmGameAdapter;

private:
    /*!
     * @brief The Game Board (Model).
     *
     * Holds the grid data and validates win logic.
     * Initialized via the Member Initialization List in the constructor.
     */
    CBoard m_board;

    /*!
     * @brief The Display System (View).
     *
     * Handles printing the board and messages to the console.
     */
    CDisplay m_display;

    /*!
     * @brief Polymorphic array of Player pointers.
     *
     * Stores pointers to two players. Depending on the game type,
     * these may point to CHuman or CComputer objects.
     * @note Memory is allocated in the constructor and freed in the destructor.
     */
    CPlayer* m_players[2];

    /*!
     * @brief Tracks the current turn.
     *
     * Value is 0 for Player 1, 1 for Player 2.
     * Used as an index to access m_players[].
     */
    unsigned int m_currentPlayerIdx;

    /*!
     * @brief Main loop control flag.
     *
     * True while the game is active; set to False when a Win or Draw occurs.
     */
    bool m_isRunning;

public:
    /*!
     * @brief Constructor. Initializes the game environment.
     *
     * @param boardSize The dimension of the grid (e.g., 3 for 3x3).
     * @param gameType The mode of play (HvH, HvC, CvC).
     * @throws std::invalid_argument If the board size violates CBoard constraints.
     */
    CGame(unsigned int boardSize, EGameType gameType);

    /*!
     * @brief Destructor.
     *
     * Cleanly deletes the player objects allocated on the heap to prevent memory leaks.
     */
    virtual ~CGame();

    /*!
     * @brief Starts the main game loop.
     *
     * This function blocks until the game ends. It orchestrates the flow:
     * Display Board -> Get Move -> Update Board -> Check Win -> Switch Player.
     */
    void playGame();

    /*!
     * @brief Gets the index of the player whose turn it is.
     * @return 0 or 1.
     */
    unsigned int getCurrentPlayerIdx() const;

    /*!
     * @brief Prints configuration details to the console.
     *
     * Displays which player is Human/Computer and what symbol (X/O) they hold.
     */
    void printPlayerInfo() const;

private:
    /*!
     * @brief Toggles the current player index.
     *
     * Switches m_currentPlayerIdx from 0 to 1, or 1 to 0.
     */
    void m_switchPlayer();

    /*!
     * @brief Helper to allocate player objects and assign symbols.
     *
     * Uses a random coin toss to determine who gets 'X' (First turn).
     * Allocates new CHuman or CComputer objects into m_players[].
     *
     * @param gameType The selected game mode (HvH, HvC, CvC).
     */
    void m_symbolInit(EGameType gameType);

    /*!
     * @brief Checks if the game has ended based on the last move.
     *
     * Queries the CBoard for win/draw status. If the game is over,
     * it prints the result via CDisplay and sets m_isRunning to false.
     *
     * @param currentPlayer Pointer to the player who just made a move (for printing winner info).
     */
    void m_checkResult(CPlayer *currentPlayer);
};

#endif /* CGAME_H_ */
