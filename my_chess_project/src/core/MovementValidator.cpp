// src/core/MovementValidator.cpp
#include "MovementValidator.hpp"
#include <cmath>
#include <string>

namespace core
{
    bool MovementValidator::isValidMove(const Board &board, int fromRow, int fromCol, int toRow, int toCol)
    {
        std::string piece = board.getCell(fromRow, fromCol);
        if (piece == ".")
            return false;

        char type = piece[1];
        int dr = toRow - fromRow;
        int dc = toCol - fromCol;

        if (dr == 0 && dc == 0)
            return false;

        if (type == 'K')
        {
            return std::abs(dr) <= 1 && std::abs(dc) <= 1;
        }

        if (type == 'N')
        {
            return (std::abs(dr) == 1 && std::abs(dc) == 2) || (std::abs(dr) == 2 && std::abs(dc) == 1);
        }

        bool isStraight = (dr == 0 || dc == 0);
        bool isDiagonal = (std::abs(dr) == std::abs(dc));

        if (type == 'R' && !isStraight)
            return false;

        if (type == 'B' && !isDiagonal)
            return false;

        if (type == 'Q' && !isStraight && !isDiagonal)
            return false;

        if (type == 'P')
        {
            char color = piece[0];
            int dir = (color == 'w') ? -1 : 1;

            if (dr == dir && dc == 0)
            {
                return board.getCell(toRow, toCol) == ".";
            }

            if (dr == dir && std::abs(dc) == 1)
            {
                std::string target = board.getCell(toRow, toCol);
                return target != "." && target[0] != color;
            }

            return false;
        }

        if (type == 'R' || type == 'B' || type == 'Q')
        {
            int stepR = (dr == 0) ? 0 : (dr > 0 ? 1 : -1);
            int stepC = (dc == 0) ? 0 : (dc > 0 ? 1 : -1);

            int currR = fromRow + stepR;
            int currC = fromCol + stepC;

            while (currR != toRow || currC != toCol)
            {
                if (board.getCell(currR, currC) != ".")
                {
                    return false; 
                }
                currR += stepR;
                currC += stepC;
            }
        }

        return true;
    }
}