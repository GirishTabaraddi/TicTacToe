#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>
#include "CGame.h"
#include "CBoard.h"
#include "CPlayer.h"
#include "CComputer.h"
#include "CHuman.h"
#include <string>
#include <sstream>

using namespace emscripten;

class WasmGameAdapter {
private:
    CGame* m_game;

public:
    WasmGameAdapter(int size, int typeInt) {
        EGameType type = EGameType::HvH;
        if(typeInt == 2) type = EGameType::HvC;
        if(typeInt == 3) type = EGameType::CvC;

        m_game = new CGame(size, type);
    }

    ~WasmGameAdapter() {
        delete m_game;
    }

    std::string getPlayerInfo() {
        std::stringstream ss;
        CPlayer* p0 = m_game->m_players[0];
        CPlayer* p1 = m_game->m_players[1];

        ss << "Player 1: " << p0->getPlayerType() << " (" << (char)p0->getSymbol() << ")";
        ss << "  VS  ";
        ss << "Player 2: " << p1->getPlayerType() << " (" << (char)p1->getSymbol() << ")";

        return ss.str();
    }

    std::string getCurrentTurnInfo() {
        if(!m_game->m_isRunning) return "Game Over";
        CPlayer* curr = m_game->m_players[m_game->m_currentPlayerIdx];
        std::string s = "Turn: ";
        s += (char)curr->getSymbol();
        s += " (" + curr->getPlayerType() + ")";
        return s;
    }

    std::string getBoardState() {
        std::string result = "";
        int rows = m_game->m_board.getRows();
        int cols = m_game->m_board.getCols();

        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                EBoardState cell = m_game->m_board.getCellValue(r, c);
                if(cell == EBoardState::X) result += "x";
                else if(cell == EBoardState::O) result += "o";
                else result += ".";
            }
        }
        return result;
    }

    std::string clickCell(int row, int col) {
        if(!m_game->m_isRunning) return "GAME_OVER";

        CPlayer* curr = m_game->m_players[m_game->m_currentPlayerIdx];

        if(curr->getPlayerType() == "Computer") return "WAITING_FOR_COMPUTER";

        if(m_game->m_board.getCellValue(row, col) != EBoardState::EMPTY) {
            return "INVALID";
        }

        m_game->m_board.setCellValue(row, col, curr->getSymbol());

        EGameResult res = m_game->m_board.checkWinStatus();
        if(res != EGameResult::PLAYING) {
            m_game->m_isRunning = false;
            return resultToString(res);
        }

        m_game->m_switchPlayer();

        curr = m_game->m_players[m_game->m_currentPlayerIdx];
        if(curr->getPlayerType() == "Computer" && m_game->m_isRunning) {
            return computerStep();
        }

        return "PLAYING";
    }

    std::string computerStep() {
        if(!m_game->m_isRunning) return "GAME_OVER";

        CPlayer* curr = m_game->m_players[m_game->m_currentPlayerIdx];

        if(curr->getPlayerType() != "Computer") return "WAITING_FOR_HUMAN";

        Coordinates aiMove = curr->decideMove(m_game->m_board);
        m_game->m_board.setCellValue(aiMove.row, aiMove.col, curr->getSymbol());

        EGameResult res = m_game->m_board.checkWinStatus();
        if(res != EGameResult::PLAYING) {
            m_game->m_isRunning = false;
            return resultToString(res);
        }

        m_game->m_switchPlayer();

        return "PLAYING";
    }

    bool isComputerTurn() {
        if(!m_game->m_isRunning) return false;
        CPlayer* curr = m_game->m_players[m_game->m_currentPlayerIdx];
        return (curr->getPlayerType() == "Computer");
    }

private:
    std::string resultToString(EGameResult res) {
        if(res == EGameResult::X_WINS) return "X_WINS";
        if(res == EGameResult::O_WINS) return "O_WINS";
        if(res == EGameResult::DRAW) return "DRAW";
        return "PLAYING";
    }
};

EMSCRIPTEN_BINDINGS(my_module) {
    class_<WasmGameAdapter>("TicTacToe")
        .constructor<int, int>()
        .function("clickCell", &WasmGameAdapter::clickCell)
        .function("computerStep", &WasmGameAdapter::computerStep)
        .function("getBoardState", &WasmGameAdapter::getBoardState)
        .function("getPlayerInfo", &WasmGameAdapter::getPlayerInfo)
        .function("getCurrentTurnInfo", &WasmGameAdapter::getCurrentTurnInfo)
        .function("isComputerTurn", &WasmGameAdapter::isComputerTurn);
}
#endif
