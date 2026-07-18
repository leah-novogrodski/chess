#pragma once

#include "img.hpp"
#include "../engine/GameSnapshot.hpp"

void drawPiece(Img& canvas, const PieceSnapshot& piece);


void drawSelection(Img& canvas, const std::optional<Position>& selectedCell);


Img renderFrame(const GameSnapshot& snapshot);

void drawGameOver(Img& canvas, int canvasWidth, int canvasHeight);