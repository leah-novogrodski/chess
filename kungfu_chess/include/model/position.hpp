#pragma once

#include <iosfwd>

struct Position {
    int row;
    int col;

    Position() ;
    Position(int row, int col);

    bool operator==(Position const& other) const;
    bool operator!=(Position const& other) const ;
};

