#pragma once

#include "img.hpp"
#include <string>
#include "../model/Piece.hpp"


namespace SpriteLoader {
std::string pieceCodeFromPiece(Color color, Kind kind);

extern const std::string PIECES_ROOT;

Img loadPieceIdleSprite(const std::string& pieceCode);
Img loadPieceIdleSprite(const std::string& pieceCode, const std::string& state);

}  // namespace SpriteLoader
