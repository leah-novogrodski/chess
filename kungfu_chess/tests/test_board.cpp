#include "doctest.h"
#include "model/board.hpp"
#include "model/position.hpp"
#include <memory>
#include <stdexcept>

TEST_CASE("Board initialization and boundaries") {
    Board board(8, 8);

    CHECK(board.is_valid_position(Position{0, 0}) == true);
    CHECK(board.is_valid_position(Position{7, 7}) == true);
    CHECK(board.is_valid_position(Position{8, 8}) == false);
    CHECK(board.is_valid_position(Position{-1, 4}) == false);
}

TEST_CASE("Board exception handling for empty positions") {
    Board board(8, 8);
    Position pos{3, 3};

    CHECK(board.is_empty(pos) == true);
    CHECK_THROWS_AS(board.remove_piece(pos), std::logic_error);
}

TEST_CASE("Board out of bounds exceptions") {
    Board board(8, 8);
    Position out_of_bounds{10, 10};

    CHECK_THROWS_AS(board.is_empty(out_of_bounds), std::out_of_range);
}