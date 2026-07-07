#ifndef BOARDPARSER_HPP
#define BOARDPARSER_HPP

#include <vector>
#include <string>

class BoardParser
{
public:

    std::vector<std::string> readBoard();

    bool validateBoard(
        const std::vector<std::string>& board
    );

    void printBoard(
        const std::vector<std::string>& board
    );
};


#endif