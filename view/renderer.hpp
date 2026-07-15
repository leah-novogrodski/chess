#pragma once

#include "img.hpp"
#include "GameSnapshot.hpp"

void drawPiece(Img& canvas, const PieceSnapshot& piece);

// Draws the board, then every piece in snapshot.pieces, in order.
Img renderFrame(const GameSnapshot& snapshot);

Img& getCachedPieceSprite(const std::string& pieceCode, const std::string& state);