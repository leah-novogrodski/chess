#include "piece.hpp"

#include <ostream>

namespace chess
{

    Piece::Piece() noexcept = default;

    Piece::Piece(PieceId id, Color color, Type type, Position square, State state) noexcept
        : id(id), color(color), type(type), square(square), state(state) {}

    bool Piece::operator==(Piece const &other) const noexcept
    {
        return id == other.id && color == other.color && type == other.type && square == other.square && state == other.state;
    }

    bool Piece::operator!=(Piece const &other) const noexcept
    {
        return !(*this == other);
    }

    namespace
    {

        const char *toString(Color color) noexcept
        {
            return (color == Color::White) ? "White" : "Black";
        }

        const char *toString(Type type) noexcept
        {
            switch (type)
            {
            case Type::King:
                return "King";
            case Type::Queen:
                return "Queen";
            case Type::Rook:
                return "Rook";
            case Type::Bishop:
                return "Bishop";
            case Type::Knight:
                return "Knight";
            case Type::Pawn:
                return "Pawn";
            }
            return "Unknown";
        }

        const char *toString(State state) noexcept
        {
            switch (state)
            {
            case State::Idle:
                return "Idle";
            case State::Moving:
                return "Moving";
            case State::Captured:
                return "Captured";
            }
            return "Unknown";
        }

    }

    std::ostream &operator<<(std::ostream &os, Piece const &piece)
    {
        return os << "Piece{id=" << piece.id
                  << ", color=" << toString(piece.color)
                  << ", type=" << toString(piece.type)
                  << ", square=" << piece.square
                  << ", state=" << toString(piece.state)
                  << "}";
    }

}
