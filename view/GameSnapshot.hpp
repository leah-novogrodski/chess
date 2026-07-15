#pragma once

#include <optional>
#include <string>
#include <vector>

#include "../model/GameState.hpp"

struct PieceSnapshot {
    std::string pieceCode;     // from pieceCodeFromPiece
    int pixelX, pixelY;        // top-left pixel position of this piece's cell
    std::string animState;     // "move" if isPieceCurrentlyMoving(cell) is true, else "idle"
};

struct GameSnapshot {
    int rows, cols;
    std::vector<PieceSnapshot> pieces;
    std::optional<Position> selectedCell;   // from state.selection, only if selection.active
    bool gameOver;
};

GameSnapshot buildSnapshot(const GameState& state);