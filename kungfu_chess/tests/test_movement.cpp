
#include "doctest.h"
#include "include/core/GameEngine.hpp"
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

TEST_CASE("GameEngine - Blockers and Captures") {
    std::istringstream input(
        "Board:\n"
        "wR bP . wB\n"
        ".  .  .  .\n"
        "wN bP .  .\n"
        "Commands:\n"
    );
    core::Board board = core::Board::parse(input);
    core::GameEngine engine(board);

    SUBCASE("Rook and Bishop cannot move THROUGH another piece") {
        // 1. נסיון להזיז את הצריח הלבן (0,0) ימינה מעבר לחייל השחור שב-(0,1) אל התא (0,2)
        engine.click(50, 50);   // בחירת wR
        engine.click(250, 50);  // לחיצה על (0,2) - חסום על ידי bP
        CHECK(engine.getBoard().getCell(0, 0) == "wR"); // התנועה נפרצה, הצריח נשאר במקום

        // 2. נסיון להזיז את הרץ הלבן (0,3) שמאלה-למטה מעבר לחייל השחור שב-(2,1)
        // מסלול אלכסוני מ-(0,3) ל-(3,0) עובר דרך (1,2) ו-(2,1). ב-(2,1) יש bP חוסם.
        engine.click(350, 50);  // בחירת wB
        engine.click(50, 350);  // לחיצה על (3,0) - חסום!
        CHECK(engine.getBoard().getCell(0, 3) == "wB"); // הרץ נשאר במקום
    }

    SUBCASE("Knight CAN jump over blockers") {
        // הפרש הלבן נמצא ב-(2,0). הוא רוצה לזוז ל-(0,1) בצעד L.
        // בדרך (בשורות או בעמודות הביניים) יש כלים, אך פרש אמור לדלג מעליהם.
        engine.click(50, 250);  // בחירת wN
        engine.click(150, 50);  // לחיצה על (0,1) שבו נמצא bP
        
        // הפרש אמור לבצע את התנועה בהצלחה וללכוד את ה-bP
        CHECK(engine.getBoard().getCell(0, 1) == "wN");
        CHECK(engine.getBoard().getCell(2, 0) == ".");
    }

    SUBCASE("Piece cannot capture its own color, but can capture enemy") {
        // 1. אכילת אויב חוקית: צריח לבן ב-(0,0) אוכל חייל שחור ב-(0,1)
        engine.click(50, 50);   // בחירת wR
        engine.click(150, 50);  // לחיצה על bP ב-(0,1)
        CHECK(engine.getBoard().getCell(0, 1) == "wR"); // האכילה הצליחה!
        CHECK(engine.getBoard().getCell(0, 0) == ".");

        // 2. מניעת אכילה עצמית: ננסה להביא את הרץ הלבן ב-(0,3) לאכול את הצריח הלבן החדש ב-(0,1)
        // מכיוון שהם מאותו הצבע ('w'), זה פשוט צריך להעביר את הבחירה לרץ, ולא לבצע אכילה.
        engine.click(350, 50);  // בחירת wB
        engine.click(150, 50);  // לחיצה על wR (ידיד)
        
        // הבחירה הייתה אמורה לעבור ל-wR, והרץ wB נשאר במקומו ב-(0,3)
        CHECK(engine.getBoard().getCell(0, 3) == "wB");
        CHECK(engine.getBoard().getCell(0, 1) == "wR");
    }
}