#include <iostream>
#include "BoardParser.hpp"


int main()
{
    BoardParser parser;


    auto board = parser.readBoard();


    if(parser.validateBoard(board))
    {
        parser.printBoard(board);
    }


    return 0;
}