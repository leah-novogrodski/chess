#include "model/position.hpp"

#include <ostream>

Position::Position(int row, int col)  : row(row), col(col) {}

bool Position::operator==(Position const& other) const noexcept {
    return row == other.row && col == other.col;
}

bool Position::operator!=(Position const& other) const noexcept {
    return !(*this == other);
}


