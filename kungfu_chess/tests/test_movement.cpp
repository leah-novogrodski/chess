
#include "doctest.h"
#include "../include/core/GameEngine.hpp"
#include <sstream>

TEST_CASE("GameEngine - Piece Movement Patterns") {
    std::istringstream input(
        "Board:\n"
        "wK . . wR . . .\n"
        ". . . . . . .\n"
        ". bB . . . . .\n"
        ". . . wQ . . .\n"
        ". wN . . . . .\n"
        "Commands:\n"
    );
    core::Board board = core::Board::parse(input);
    core::GameEngine engine(board);

    SUBCASE("King: 1 step valid, 2 steps ignored") {
        // Select wK at (0,0) -> click(50, 50)
        engine.click(50, 50);
        // Try illegal move: 2 cells right to (0,2) -> click(250, 50)
        engine.click(250, 50);
        CHECK(engine.getBoard().getCell(0, 0) == "wK"); // Ignored, stays at (0,0)

        // Select wK again and move 1 step diagonally down-right to (1,1)
        engine.click(50, 50);
        engine.click(150, 150);
        CHECK(engine.getBoard().getCell(1, 1) == "wK");
        CHECK(engine.getBoard().getCell(0, 0) == ".");
    }

    SUBCASE("Rook: Straight valid, Diagonal ignored") {
        // Select wR at (0,3) -> click(350, 50)
        engine.click(350, 50);
        // Try illegal diagonal move to (1,4) -> click(450, 150)
        engine.click(450, 150);
        CHECK(engine.getBoard().getCell(0, 3) == "wR"); // Ignored

        // Valid straight move down to (2,3)
        engine.click(350, 50);
        engine.click(350, 250);
        CHECK(engine.getBoard().getCell(2, 3) == "wR");
    }

    SUBCASE("Bishop: Diagonal valid, Straight ignored, and path blocking") {
        // Select bB at (2,1) -> click(150, 250)
        engine.click(150, 250);
        // Try illegal straight move -> click(150, 50)
        engine.click(150, 50);
        CHECK(engine.getBoard().getCell(2, 1) == "bB");

        // Valid diagonal move to (0,3) but it's blocked by wR! Should be ignored
        engine.click(150, 250);
        engine.click(350, 50);
        CHECK(engine.getBoard().getCell(2, 1) == "bB");
    }

    SUBCASE("Knight: L-shape valid") {
        // Select wN at (4,1) -> click(150, 450)
        engine.click(150, 450);
        // Valid L-move to (2,2) -> click(250, 250)
        engine.click(250, 250);
        CHECK(engine.getBoard().getCell(2, 2) == "wN");
    }
}