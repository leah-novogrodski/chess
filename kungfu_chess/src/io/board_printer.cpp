#pragma once

#include <vector>
#include <string>
#include <ostream>
#include <memory>

class BoardPrinter {
public:
    static std::unique_ptr<BoardPrinter> create();

    void print(std::ostream& output, const std::vector<std::vector<std::string>>& board) const;
};