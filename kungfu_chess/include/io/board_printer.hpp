#pragma once

#include <vector>
#include <string>
#include <ostream>
#include <memory>

class BoardPrinter {
public:
    static std::unique_ptr<BoardPrinter> create();
    void print(const Board& board) const;
};