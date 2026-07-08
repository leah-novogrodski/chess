#include "GameEngine.hpp"
#include "MovementValidator.hpp"

namespace core {
    GameEngine::GameEngine(const Board& initialBoard) 
        : board(initialBoard), clockMs(0), hasSelection(false), selectedRow(-1), selectedCol(-1) {}

    void GameEngine::click(int x, int y) {
        int col = x / CELL_SIZE;
        int row = y / CELL_SIZE;

        if (row < 0 || row >= board.getRows() || col < 0 || col >= board.getCols()) {
            return;
        }

        std::string clickedPiece = board.getCell(row, col);

        if (!hasSelection) {
            if (clickedPiece != ".") {
                hasSelection = true;
                selectedRow = row;
                selectedCol = col;
            }
        } else {
            std::string selectedPiece = board.getCell(selectedRow, selectedCol);
            if (row == selectedRow && col == selectedCol) return;

            if (clickedPiece != "." && clickedPiece[0] == selectedPiece[0]) {
                selectedRow = row;
                selectedCol = col;
            } 
            else {
                if (MovementValidator::isValidMove(board, selectedRow, selectedCol, row, col)) {
                    board.setCell(row, col, selectedPiece);
                    board.setCell(selectedRow, selectedCol, ".");
                }
                hasSelection = false;
            }
        }
    }

    void GameEngine::wait(int ms) {
        if (ms > 0) {
            clockMs += ms;
        }
    }

    void GameEngine::printBoard(std::ostream& out) const {
        board.print(out);
    }

    bool GameEngine::hasActiveSelection() const { return hasSelection; }
    uint64_t GameEngine::getClockMs() const { return clockMs; }
    const Board& GameEngine::getBoard() const { return board; }
}