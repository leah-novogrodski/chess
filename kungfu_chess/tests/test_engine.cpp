// tests/test_engine.cpp
#include "doctest.h"
#include "../include/core/GameEngine.hpp"
#include <sstream>
#include <Board.hpp>

TEST_CASE("GameEngine - Click and Selection Logic") {
    std::istringstream input(
        "wK . bK\n"
        ". wR .\n"
        ". . bR\n"
    );
    core::Board board = core::Board::parse(input);
    core::GameEngine engine(board);

    SUBCASE("Clicking out of bounds is ignored") {
        engine.click(-50, 50);  // Negative X
        engine.click(400, 50);  // X out of bounds (max 300)
        CHECK_FALSE(engine.hasActiveSelection());
    }

    SUBCASE("Clicking empty cell without selection is ignored") {
        engine.click(150, 50); // Row 0, Col 1 (Empty '.')
        CHECK_FALSE(engine.hasActiveSelection());
    }

    SUBCASE("Select piece, change selection to friendly, then move") {
        // 1. Select white King ('wK' at 0,0) -> click(50, 50)
        engine.click(50, 50);
        CHECK(engine.hasActiveSelection());

        // 2. Click friendly white Rook ('wR' at 1,1) -> click(150, 150)
        // Should replace selection, not capture!
        engine.click(150, 150);
        CHECK(engine.hasActiveSelection());

        // 3. Move selected 'wR' to empty cell at 2,0 -> click(50, 250)
        engine.click(50, 250);
        CHECK_FALSE(engine.hasActiveSelection()); // Selection clears after move
        
        // Verify board state
        CHECK(engine.getBoard().getCell(2, 0) == "wR");
        CHECK(engine.getBoard().getCell(1, 1) == "."); // Original cell is empty
    }

    SUBCASE("Select piece and capture enemy") {
        // Select 'wR' at 1,1 -> click(150, 150)
        engine.click(150, 150);
        
        // Click enemy 'bR' at 2,2 -> click(250, 250)
        engine.click(250, 250);
        
        CHECK(engine.getBoard().getCell(2, 2) == "wR"); // Captured!
        CHECK(engine.getBoard().getCell(1, 1) == ".");
    }

    SUBCASE("Wait advances clock") {
        CHECK(engine.getClockMs() == 0);
        engine.wait(500);
        CHECK(engine.getClockMs() == 500);
        engine.wait(200);
        CHECK(engine.getClockMs() == 700);
    }
}