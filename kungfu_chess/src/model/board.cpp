#include "model/board.hpp"
#include <stdexcept>

Board::Board(int width, int height)
    : m_width(width), m_height(height) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Invalid board dimensions");
    }
    m_grid.resize(m_width * m_height);
}

int Board::calculate_index(const Position& pos) const {
    if (!is_valid_position(pos)) {
        throw std::out_of_range("Position out of bounds");
    }
    return pos.row * m_width + pos.col;
}

bool Board::is_valid_position(const Position& pos) const {
    return pos.col >= 0 && pos.col < m_width &&
           pos.row >= 0 && pos.row < m_height;
}

bool Board::is_empty(const Position& pos) const {
    if (!is_valid_position(pos)) {
        throw std::out_of_range("Position out of bounds");
    }
    return !m_grid[calculate_index(pos)].has_value();
}

std::optional<chess::Piece> Board::get_piece(const Position& pos) const {
    if (!is_valid_position(pos)) {
        throw std::out_of_range("Position out of bounds");
    }
    return m_grid[calculate_index(pos)];
}

void Board::add_piece(const Position& pos, const chess::Piece &piece) {
    if (!is_valid_position(pos)) {
        throw std::out_of_range("Position out of bounds");
    }

    int index = calculate_index(pos);

    if (m_grid[index].has_value()) {
        throw std::logic_error("Position already occupied");
    }

    m_grid[index] = piece;
}

void Board::remove_piece(const Position& pos) {
    if (!is_valid_position(pos)) {
        throw std::out_of_range("Position out of bounds");
    }

    int index = calculate_index(pos);

    if (!m_grid[index].has_value()) {
        throw std::logic_error("Position is already empty");
    }

    m_grid[index] = std::nullopt;
}

void Board::move_piece(const Position& from, const Position& to) {
    if (!is_valid_position(from) || !is_valid_position(to)) {
        throw std::out_of_range("Position out of bounds");
    }

    int from_index = calculate_index(from);
    int to_index = calculate_index(to);

    if (!m_grid[from_index].has_value()) {
        throw std::logic_error("Source position is empty");
    }

    if (m_grid[to_index].has_value()) {
        throw std::logic_error("Target position is occupied");
    }

    m_grid[to_index] = m_grid[from_index];
    m_grid[from_index] = std::nullopt;
}