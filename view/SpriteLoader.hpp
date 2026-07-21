#pragma once

#include "img.hpp"
#include <string>


namespace SpriteLoader
{

    inline const std::string PIECES_ROOT = "assets/pieces_classic/";

    std::string pieceCodeFromPiece(Color color, Kind kind);

    Img &getCachedPieceSprite(const std::string &pieceCode, const std::string &state);

    Img &getCachedPieceFrame(const std::string &pieceCode, const std::string &state, int frameIndex);

}