
#include "Board.hpp"
#include <stdexcept>
#include <sstream>

namespace core
{

    static std::string trim(const std::string &str)
    {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == std::string::npos)
            return "";
        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, (last - first + 1));
    }

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

    Board Board::parse(std::istream &in)
    {
        Board board;
        std::string line;
        size_t expectedWidth = 0;

        while (std::getline(in, line))
        {
            line = trim(line);

            if (line.empty())
                continue;
            if (line == "Board:")
                continue;
            if (line.back() == ':')
                break;

            std::istringstream iss(line);
            std::vector<std::string> row;
            std::string cell;

            while (iss >> cell)
            {
                if (!isValidCell(cell))
                {
                    throw std::runtime_error("ERROR UNKNOWN_TOKEN");
                }
                row.push_back(cell);
            }

            if (row.empty())
                continue;

            if (board.grid.empty())
            {
                expectedWidth = row.size();
            }
            else if (row.size() != expectedWidth)
            {
                throw std::runtime_error("ERROR ROW_WIDTH_MISMATCH");
            }

            board.grid.push_back(row);
        }

        return board;
    }

    void Board::print(std::ostream &out) const
    {
        for (const auto &row : grid)
        {
            for (size_t i = 0; i < row.size(); ++i)
            {
                out << row[i] << (i + 1 < row.size() ? " " : "");
            }
            out << '\n';
        }
    }

    int Board::getRows() const { return grid.size(); }
    int Board::getCols() const { return grid.empty() ? 0 : grid[0].size(); }

    std::string Board::getCell(int row, int col) const
    {
        return grid[row][col];
    }
    
    void Board::setCell(int row, int col, const std::string &value)
    {
        grid[row][col] = value;
    }

}