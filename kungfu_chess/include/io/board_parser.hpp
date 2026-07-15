#pragma once

#include <vector>
#include <string>
#include <istream>
#include <unordered_set>
#include <memory>
#include <optional>
#include "model/board.hpp"

class BoardParser {
public:
    Board readBoard(std::istream &in) const;

private:
    bool isValidToken(const std::string& token) const;
    std::vector<std::string> parseRow(const std::string& line) const;
    Board readBoard(std::istream &in);
};