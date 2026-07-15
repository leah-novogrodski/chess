#include "model/piece.hpp"

#include <ostream>
#include <unordered_map>
namespace
{
    const std::unordered_map<char, chess::Type> pieceTypes{
        {'K', chess::Type::King},
        {'Q', chess::Type::Queen},
        {'R', chess::Type::Rook},
        {'B', chess::Type::Bishop},
        {'N', chess::Type::Knight},
        {'P', chess::Type::Pawn}};
}

namespace chess
{

    Piece::Piece(PieceId id, Color color, Type type, Position square, State state)
        : id(id), color(color), type(type), square(square), state(state) {}

    Type Piece::typeFromChar(char c)
    {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));

        auto it = pieceTypes.find(c);
        if (it == pieceTypes.end())
        {
            throw std::runtime_error("Unknown piece type");
        }

        return it->second;
    }

    Color Piece::colorFromChar(char c)
    {
        return std::isupper(static_cast<unsigned char>(c))
                   ? Color::White
                   : Color::Black;
    }

    bool Piece::operator==(Piece const &other) const
    {
        return id == other.id && color == other.color && type == other.type && square == other.square && state == other.state;
    }

    bool Piece::operator!=(Piece const &other) const
    {
        return !(*this == other);
    }

    namespace
    {

        const char *toString(Color color)
        {
            return (color == Color::White) ? "White" : "Black";
        }

        const char *toString(Type type)
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

        const char *toString(State state)
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
                  << ", state=" << toString(piece.state)
                  << "}";
    }

}
