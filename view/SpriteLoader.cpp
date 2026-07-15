#include "SpriteLoader.hpp"
#include "../model/Piece.hpp"
#include "../rules/Config.hpp"

namespace SpriteLoader {

std::string pieceCodeFromPiece(Color color, Kind kind) {
    char kindChar = 'K';
    switch (kind) {
        case Kind::King:   kindChar = 'K'; break;
        case Kind::Queen:  kindChar = 'Q'; break;
        case Kind::Rook:   kindChar = 'R'; break;
        case Kind::Bishop: kindChar = 'B'; break;
        case Kind::Knight: kindChar = 'N'; break;
        case Kind::Pawn:   kindChar = 'P'; break;
    }
    char colorChar = (color == Color::White) ? 'W' : 'B';
    return std::string{kindChar, colorChar};
}

const std::string PIECES_ROOT = "assets/pieces_classic/pieces_classic/";

Img loadPieceIdleSprite(const std::string& pieceCode) {
    return loadPieceIdleSprite(pieceCode, "idle");
}

Img loadPieceIdleSprite(const std::string& pieceCode, const std::string& state) {
    const std::string path = PIECES_ROOT + pieceCode + "/states/" + state + "/sprites/1.png";
    Img image;
    image.read(path, {config::CELL_SIZE, config::CELL_SIZE}, true);
    return image;
}

}  

