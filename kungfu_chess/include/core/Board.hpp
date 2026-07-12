#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace core {
 class Board {
    public:
        static Board parse(std::istream& in);    
        void print(std::ostream& out) const;

        int getRows() const;
        int getCols() const;
        std::string getCell(int row, int col) const;
        void setCell(int row, int col, const std::string &value);

    private:
        std::vector<std::vector<std::string>> grid;
        static bool isValidCell(const std::string &cell);
    };
}