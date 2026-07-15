#pragma once

#include <vector>
#include <string>
#include <ostream>
#include <memory>
#include <iostream>
#include "model/board.hpp"
#include "model/piece.hpp"

class BoardPrinter {



void BoardPrinter::print(const Board& board) const
{
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            auto piece = board.get_piece(Position{col, row});

            if (!piece.has_value())
            {
                std::cout << ". ";
                continue;
            }

            std::cout << piece.value() << ' ';
        }

        std::cout << '\n';
    }
}};