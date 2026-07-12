// src/core/MovementValidator.cpp
#include "../../include/core/MovementValidator.hpp"
#include <cmath>
#include <string>

namespace core {
    bool MovementValidator::isValidMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol) {
        std::string piece = board.getCell(fromRow, fromCol);
        if (piece == ".") return false;
        
        char type = piece[1];
        int dr = toRow - fromRow;
        int dc = toCol - fromCol;

        // תנועה לאותו תא בדיוק אינה חוקית
        if (dr == 0 && dc == 0) return false;

        // 1. מלך (K) - צעד אחד לכל כיוון
        if (type == 'K') {
            return std::abs(dr) <= 1 && std::abs(dc) <= 1;
        }

        // 2. פרש (N) - תנועת L (בריבוע: 1 ו-2 או 2 ו-1)
        if (type == 'N') {
            return (std::abs(dr) == 1 && std::abs(dc) == 2) || (std::abs(dr) == 2 && std::abs(dc) == 1);
        }

        // הגדרת כיווני תנועה בסיסיים עבור הכלים המחליקים
        bool isStraight = (dr == 0 || dc == 0);
        bool isDiagonal = (std::abs(dr) == std::abs(dc));

        // 3. צריח (R) - רק ישר
        if (type == 'R' && !isStraight) return false;
        
        // 4. רץ (B) - רק באלכסון
        if (type == 'B' && !isDiagonal) return false;
        
        // 5. מלכה (Q) - ישר או באלכסון
        if (type == 'Q' && !isStraight && !isDiagonal) return false;

        // בדיקת חסימות נתיב (Path Blocking) עבור R, B, Q
        if (type == 'R' || type == 'B' || type == 'Q') {
            // קביעת כיוון הצעד (-1, 0, או 1)
            int stepR = (dr == 0) ? 0 : (dr > 0 ? 1 : -1);
            int stepC = (dc == 0) ? 0 : (dc > 0 ? 1 : -1);

            int currR = fromRow + stepR;
            int currC = fromCol + stepC;

            // סריקת כל התאים בדרך עד (אך לא כולל) תא היעד
            while (currR != toRow || currC != toCol) {
                if (board.getCell(currR, currC) != ".") {
                    return false; // יש כלי שחוסם את הנתיב
                }
                currR += stepR;
                currC += stepC;
            }
        }

        return true;
    }
}