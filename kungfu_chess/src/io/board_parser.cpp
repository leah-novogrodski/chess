#include <iostream>
#include <sstream>
#include <set>
#include "model/board_parser.hpp"

bool isValidToken(const std::string &token)
{
    static std::set<std::string> valid =
        {
            ".",
            "wK", "bK",
            "wQ", "bQ",
            "wR", "bR",
            "wB", "bB",
            "wN", "bN",
            "wP", "bP"};

    return valid.count(token);
}

Board BoardParser::readBoard(std::istream &in)
{
    int width;
    int height;

    in >> width >> height;

    Board board(width, height);

    chess::PieceId nextId = 0;

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            char symbol;
            in >> symbol;

            if (symbol == '.')
            {
                continue;
            }

            auto piece = std::make_shared<chess::Piece>(
                nextId++,
                chess::Piece::colorFromChar(symbol),
                chess::Piece::typeFromChar(symbol),
                Position{col, row});

            board.add_piece(Position{col, row}, *piece);
        }
    }

    return board;
}
