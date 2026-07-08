// src/core/Board.cpp
#include "../../include/core/Board.hpp"
#include <stdexcept>
#include <sstream>

namespace core
{

    bool Board::isValidCell(const std::string &cell)
    {
        if (cell == ".")
            return true;

        if (cell.length() == 2)
        {
            char color = cell[0];
            char piece = cell[1];

            bool validColor = (color == 'w' || color == 'b');
            bool validPiece = (piece == 'K' || piece == 'Q' || piece == 'R' ||
                               piece == 'B' || piece == 'N' || piece == 'P' || piece == 'D');

            return validColor && validPiece;
        }

        return false;
    }

    std::vector<std::vector<std::string>> Board::parse(std::istream &in)
    {
        std::vector<std::vector<std::string>> board;
        std::string line;
        size_t expectedWidth = 0;

        while (std::getline(in, line))
        {
            if (!line.empty() && line.back() == '\r')
            {
                line.pop_back();
            }

            if (line.empty())
                continue;

            if (line == "Board:")
                continue;

            if (!line.empty() && line.back() == ':')
            {
                break;
            }

            std::istringstream iss(line);
            std::vector<std::string> row;
            std::string cell;

            while (iss >> cell)
            {
                if (!isValidCell(cell))
                {
                    throw std::invalid_argument("Invalid cell format: " + cell);
                }
                row.push_back(cell);
            }

            if (row.empty())
                continue;

            if (board.empty())
            {
                expectedWidth = row.size();
            }
            else if (row.size() != expectedWidth)
            {
                throw std::invalid_argument("Invalid board: rows have mismatched lengths.");
            }

            board.push_back(row);
        }

        if (board.empty())
        {
            throw std::invalid_argument("Invalid board: empty input.");
        }

        return board;
    }

    void Board::print(const std::vector<std::vector<std::string>> &board, std::ostream &out)
    {
        for (const auto &row : board)
        {
            for (size_t i = 0; i < row.size(); ++i)
            {
                out << row[i];
                if (i + 1 < row.size())
                {
                    out << " ";
                }
            }
            out << '\n';
        }
    }

}