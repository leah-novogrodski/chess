#pragma once

#include <optional>
#include <vector>
#include <memory>
#include "model/position.hpp"
#include "model/piece.hpp"

class Board {
public:
    Board(int width, int height);

    void remove_piece(const Position& pos);
    void add_piece(const Position& pos, std::shared_ptr<chess::Piece> piece);
    void move_piece(const Position& from, const Position& to);
    
    bool is_valid_position(const Position& pos) const;
    bool is_empty(const Position& pos) const;
    std::optional<std::shared_ptr<chess::Piece>> get_piece(const Position& pos) const;

private:
    int m_width;
    int m_height;
    std::vector<std::optional<std::shared_ptr<chess::Piece>>> m_grid;

    int calculate_index(const Position& pos) const;
};