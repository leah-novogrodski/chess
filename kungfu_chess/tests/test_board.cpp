
#include "doctest.h"
#include "../include/core/Board.hpp"
#include <sstream>

TEST_CASE("Board Parsing and Cell Validation") {
    SUBCASE("Valid custom VPL format board") {
        std::istringstream input(
            "Board:\n"
            "wK . . bK\n"
            ". . . .\n"
            "wR . . bR\n"
            "Commands:\n"
            "print board\n"
        );
        auto board = core::Board::parse(input);
        
        CHECK(board.size() == 3); // 3 rows
        CHECK(board[0].size() == 4); // 4 columns
        CHECK(board[0][0] == "wK");
        CHECK(board[0][1] == ".");
        CHECK(board[2][3] == "bR");
    }

    SUBCASE("Invalid cell - wrong color") {
        // 'x' is not a valid color (only 'w' or 'b')
        std::istringstream input("xK . . bK\n");
        CHECK_THROWS_AS(core::Board::parse(input), std::invalid_argument);
    }

    SUBCASE("Invalid cell - wrong piece type") {
        // 'X' is not a valid piece
        std::istringstream input("wX . . bK\n");
        CHECK_THROWS_AS(core::Board::parse(input), std::invalid_argument);
    }

    SUBCASE("Invalid cell - too long") {
        std::istringstream input("wK1 . . bK\n");
        CHECK_THROWS_AS(core::Board::parse(input), std::invalid_argument);
    }

    SUBCASE("Invalid board - mismatched row lengths") {
        std::istringstream input("wK . . bK\n. .\n"); 
        CHECK_THROWS_AS(core::Board::parse(input), std::invalid_argument);
    }
}