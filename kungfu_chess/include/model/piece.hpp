
#pragma once
#include "position.hpp"
#include <iosfwd>

namespace chess
{

    using PieceId = int;

    enum class Color
    {
        White,
        Black,
    };

    enum class Type
    {
        King,
        Queen,
        Rook,
        Bishop,
        Knight,
        Pawn,
    };

    enum class State
    {
        Idle,
        Moving,
        Captured,
    };

    struct Piece
    {
        PieceId id;
        Color color;
        Type type;
        Position square;
        State state;

        Piece(PieceId id, Color color, Type type, Position square, State state = State::Idle);

        bool operator==(Piece const &other) const;
        bool operator!=(Piece const &other) const;
        static Type typeFromChar(char c);
        static Color colorFromChar(char c);
    };

    std::ostream &operator<<(std::ostream &os, Piece const &piece);

} // namespace chess
