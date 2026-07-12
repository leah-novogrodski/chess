#include "doctest.h"
#include "model/position.hpp"
#include "model/piece.hpp"

#include <sstream>

using namespace chess;

TEST_CASE("Position equality") {
    Position a{1, 2};
    Position b{1, 2};
    Position c{2, 2};
    Position d{1, 3};

    CHECK_EQ(a, b);
    CHECK_NE(a, c);
    CHECK_NE(a, d);
}

TEST_CASE("Position readable representation") {
    Position p{3, 4};
    std::ostringstream os;
    os << p;
    CHECK_EQ(os.str(), "Position(3, 4)");
}

TEST_CASE("Piece model equality and readable representation") {
    Piece pawn1{1, Color::White, Type::Pawn, Position{1, 0}};
    Piece pawn2{1, Color::White, Type::Pawn, Position{1, 0}};
    Piece pawn3{2, Color::White, Type::Pawn, Position{1, 0}};
    Piece pawn4{1, Color::Black, Type::Pawn, Position{1, 0}};
    Piece pawn5{1, Color::White, Type::Pawn, Position{2, 0}};

    CHECK_EQ(pawn1, pawn2);
    CHECK_NE(pawn1, pawn3);
    CHECK_NE(pawn1, pawn4);
    CHECK_NE(pawn1, pawn5);

    std::ostringstream os;
    os << pawn1;
    CHECK_EQ(os.str(), "Piece{id=1, color=White, type=Pawn, square=Position(1, 0), state=Idle}");
}
