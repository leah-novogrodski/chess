#pragma once
#include "Board.hpp"

namespace core {
    class MovementValidator {
    public:
        static bool isValidMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol);
    };
}