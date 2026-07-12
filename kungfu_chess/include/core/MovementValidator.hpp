#pragma once
#include "Board.hpp"

namespace core {
    class MovementValidator {
    public:
        // מחזירה אמת אם התנועה מתאימה לצורת הכלי ואין כלים חוסמים בדרך
        static bool isValidMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol);
    };
}