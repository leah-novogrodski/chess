#pragma once

#include "img.hpp"
#include <string>

namespace SpriteLoader
{

    inline const std::string PIECES_ROOT = "assets/pieces_classic/";

    Img &getCachedPieceSprite(const std::string &pieceCode, const std::string &state);

    Img &getCachedPieceFrame(const std::string &pieceCode, const std::string &state, int frameIndex);

}