#include "position.hpp"

#include <ostream>

Position::Position() noexcept = default;

Position::Position(int row, int col) noexcept : row(row), col(col) {}

bool Position::operator==(Position const& other) const noexcept {
    return row == other.row && col == other.col;
}

bool Position::operator!=(Position const& other) const noexcept {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, Position const& position) {
    return os << "Position(" << position.row << ", " << position.col << ")";
}
