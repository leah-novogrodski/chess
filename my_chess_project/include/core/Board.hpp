#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace core {
    class Board {
    public:
        static std::vector<std::vector<std::string>> parse(std::istream& in);
        
        static void print(const std::vector<std::vector<std::string>>& board, std::ostream& out);

    private:
        static bool isValidCell(const std::string& cell);
    };
}