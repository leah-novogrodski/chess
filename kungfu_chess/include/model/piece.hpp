

#include "position.hpp"
#include <iosfwd>

namespace chess {

using PieceId = int;

enum class Color {
    White,
    Black,
};

enum class Type {
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn,
};

enum class State {
    Idle,
    Moving,
    Captured,
};

struct Piece {
    PieceId id;
    Color color;
    Type type;
    Position square;
    State state;

    Piece() noexcept;
    Piece(PieceId id, Color color, Type type, Position square, State state = State::Idle) noexcept;

    bool operator==(Piece const& other) const;
    bool operator!=(Piece const& other) const;
};

std::ostream& operator<<(std::ostream& os, Piece const& piece);

} // namespace chess
