#include "BoardParser.hpp"

#include <iostream>
#include <sstream>
#include <set>


bool isValidToken(const std::string& token)
{
    static std::set<std::string> valid =
    {
        ".",
        "wK","bK",
        "wQ","bQ",
        "wR","bR",
        "wB","bB",
        "wN","bN",
        "wP","bP"
    };

    return valid.count(token);
}


std::vector<std::string> BoardParser::readBoard()
{
    std::vector<std::string> board;

    std::string line;

    bool started = false;


    while(std::getline(std::cin,line))
    {
        if(line == "Board:")
        {
            started = true;
            continue;
        }


        if(line == "Commands:")
            break;


        if(started)
            board.push_back(line);
    }


    return board;
}


bool BoardParser::validateBoard(
    const std::vector<std::string>& board)
{
    int width = -1;


    for(auto row : board)
    {
        std::stringstream ss(row);

        std::string token;

        int count = 0;


        while(ss >> token)
        {
            if(!isValidToken(token))
            {
                std::cout 
                    << "ERROR UNKNOWN_TOKEN";

                return false;
            }

            count++;
        }


        if(width == -1)
            width = count;

        else if(width != count)
        {
            std::cout
                << "ERROR ROW_WIDTH_MISMATCH";

            return false;
        }
    }


    return true;
}


void BoardParser::printBoard(
    const std::vector<std::string>& board)
{
    for(auto row : board)
        std::cout << row << std::endl;
}