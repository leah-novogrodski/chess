#pragma once

#include <iosfwd>

struct Position {
    int row;
    int col;

    Position() noexcept;
    Position(int row, int col) noexcept;

    bool operator==(Position const& other) const noexcept;
    bool operator!=(Position const& other) const noexcept;
};

std::ostream& operator<<(std::ostream& os, Position const& position);
