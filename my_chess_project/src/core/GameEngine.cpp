#include "../../include/core/GameEngine.hpp"

namespace core {
    GameEngine::GameEngine(const Board& initialBoard) 
        : board(initialBoard), clockMs(0), hasSelection(false), selectedRow(-1), selectedCol(-1) {}

    void GameEngine::click(int x, int y) {
        // המרת קואורדינטות פיקסלים לאינדקסים של הרשת (חלוקה בשלמים נותנת את ה-Floor)
        int col = x / CELL_SIZE;
        int row = y / CELL_SIZE;

        // התעלמות מלחיצה מחוץ לגבולות
        if (row < 0 || row >= board.getRows() || col < 0 || col >= board.getCols()) {
            return;
        }

        std::string clickedPiece = board.getCell(row, col);

        if (!hasSelection) {
            // לחיצה על תא ריק ללא בחירה - מתעלמים
            if (clickedPiece != ".") {
                hasSelection = true;
                selectedRow = row;
                selectedCol = col;
            }
        } else {
            // אם כבר יש כלי נבחר
            std::string selectedPiece = board.getCell(selectedRow, selectedCol);
            
            // לחיצה על אותו התא - אפשר להשאיר נבחר או להתעלם. נתעלם.
            if (row == selectedRow && col == selectedCol) return;

            // אם לחצנו על כלי ידידותי (אותו צבע, דהיינו אות ראשונה זהה) - מחליפים בחירה
            if (clickedPiece != "." && clickedPiece[0] == selectedPiece[0]) {
                selectedRow = row;
                selectedCol = col;
            } 
            // אחרת - לחיצה על תא ריק או אויב: שולחים בקשת תנועה (כרגע, מבצעים תנועה מיידית)
            else {
                board.setCell(row, col, selectedPiece);
                board.setCell(selectedRow, selectedCol, "."); // ריקון תא המקור
                hasSelection = false; // איפוס בחירה
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