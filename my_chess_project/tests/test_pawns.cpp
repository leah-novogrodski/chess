// tests/test_pawns.cpp
#include "doctest.h"
#include "include/core/GameEngine.hpp"
#include <sstream>

TEST_CASE("GameEngine - Pawn Movement Rules") {

    std::istringstream input(
        "Board:\n"
        ".  .  .  .\n"
        ".  bP .  .\n"
        "wP wP bP .\n"
        ".  .  .  .\n"
        "Commands:\n"
    );
    core::Board board = core::Board::parse(input);
    core::GameEngine engine(board);

    SUBCASE("White pawn forward move and 2-step restriction") {
        engine.click(50, 250);
        engine.click(50, 50);
        CHECK(engine.getBoard().getCell(2, 0) == "wP"); // התנועה נדחתה, נשאר במקום

        engine.click(50, 250);
        engine.click(50, 150);
        CHECK(engine.getBoard().getCell(1, 0) == "wP");
        CHECK(engine.getBoard().getCell(2, 0) == ".");
    }

    SUBCASE("Pawns cannot capture forward") {
        engine.click(150, 250); // בחירת wP ב-(2,1)
        engine.click(150, 150); // לחיצה על bP ב-(1,1)
        
        CHECK(engine.getBoard().getCell(2, 1) == "wP"); // נשאר במקום
        CHECK(engine.getBoard().getCell(1, 1) == "bP"); // לא נאכל
    }

    SUBCASE("White pawn diagonal capture and empty diagonal restriction") {
        // 1. אכילה באלכסון חוקית: wP ב-(2,0) אוכל את bP ב-(1,1)
        engine.click(50, 250);
        engine.click(150, 150);
        CHECK(engine.getBoard().getCell(1, 1) == "wP");
        CHECK(engine.getBoard().getCell(2, 0) == ".");

        // 2. תנועה באלכסון לתא ריק אינה חוקית: wP ב-(2,1) מנסה ללכת באלכסון ל-(1,2) הריק
        engine.click(150, 250);
        engine.click(250, 150);
        CHECK(engine.getBoard().getCell(2, 1) == "wP"); // נדחה
    }

    SUBCASE("Black pawn downward movement and capture") {
        // 1. נסיון אכילה פרונטלית של השחור מ-(1,1) ל-(2,1) שבו נמצא wP - צריך להיכשל
        engine.click(150, 150); // בחירת bP
        engine.click(150, 250); // לחיצה קדימה על wP
        CHECK(engine.getBoard().getCell(1, 1) == "bP"); // נדחה

        // 2. אכילה באלכסון חוקית עבור השחור (למטה ושמאלה): מ-(1,1) אל wP ב-(2,0)
        engine.click(150, 150);
        engine.click(50, 250);
        CHECK(engine.getBoard().getCell(2, 0) == "bP");
        CHECK(engine.getBoard().getCell(1, 1) == ".");
    }
}