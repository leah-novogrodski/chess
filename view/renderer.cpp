#include "Renderer.hpp"

#include "SpriteLoader.hpp"
#include "../rules/Config.hpp"


void drawPiece(Img& canvas, const PieceSnapshot& piece) {
    Img& sprite = SpriteLoader::loadPieceIdleSprite(piece.pieceCode, piece.animState);
    sprite.draw_on(canvas, piece.pixelX, piece.pixelY);
}

Img renderFrame(const GameSnapshot& snapshot) {
    Img canvas;
    canvas.read("assets/board.png", {800, 800}, true);

    for (const PieceSnapshot& piece : snapshot.pieces) {
        drawPiece(canvas, piece);
    }
    return canvas;
}