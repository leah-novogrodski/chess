#include "Renderer.hpp"

#include "SpriteLoader.hpp"
#include "../rules/Config.hpp"
#include "../rules/Config.hpp"


namespace {
    const cv::Scalar SELECTION_HIGHLIGHT_COLOR(0, 0, 255, 255);   // bright red, BGRA
}

void drawPiece(Img& canvas, const PieceSnapshot& piece) {
    Img& sprite = SpriteLoader::getCachedPieceSprite(piece.pieceCode, piece.animState);
    sprite.draw_on(canvas, piece.pixelX, piece.pixelY);
}

void drawSelection(Img& canvas, const std::optional<Position>& selectedCell) {
    if (!selectedCell) return;

    int x = selectedCell->col * config::CELL_SIZE;
    int y = selectedCell->row * config::CELL_SIZE;
    const int thickness = 4;

    // Four thin opaque strips along the cell's edges, drawn via Img's
    // existing create()+draw_on() - no fill, so the piece underneath (if
    // any) stays fully visible.
    Img top, bottom, left, right;
    top.create(config::CELL_SIZE, thickness, SELECTION_HIGHLIGHT_COLOR);
    bottom.create(config::CELL_SIZE, thickness, SELECTION_HIGHLIGHT_COLOR);
    left.create(thickness, config::CELL_SIZE, SELECTION_HIGHLIGHT_COLOR);
    right.create(thickness, config::CELL_SIZE, SELECTION_HIGHLIGHT_COLOR);

    top.draw_on(canvas, x, y);
    bottom.draw_on(canvas, x, y + config::CELL_SIZE - thickness);
    left.draw_on(canvas, x, y);
    right.draw_on(canvas, x + config::CELL_SIZE - thickness, y);
}

Img renderFrame(const GameSnapshot& snapshot) {
    int width  = snapshot.cols * config::CELL_SIZE;
    int height = snapshot.rows * config::CELL_SIZE;

    Img canvas;
    canvas.read("assets/board.png", {width, height}, false);

    for (const PieceSnapshot& piece : snapshot.pieces) {
        drawPiece(canvas, piece);
    }

    drawSelection(canvas, snapshot.selectedCell);

    // TODO: game-over message is a separate later step.

    return canvas;
}