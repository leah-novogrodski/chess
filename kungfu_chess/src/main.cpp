#include "model/game_state.hpp"
#include "io/board_parser.hpp"
#include "io/board_printer.hpp"
#include <iostream>
#include <unordered_set>
#include <string>
#include <stdexcept>

int main() {
    try {
        std::unordered_set<std::string> validPieces = {
            ".", 
            "wK", "bK", 
            "wQ", "bQ", 
            "wR", "bR", 
            "wB", "bB", 
            "wN", "bN", 
            "wP", "bP"
        };

        auto parser = BoardParser::create(validPieces);
        auto printer = BoardPrinter::create();

        auto parsedBoardData = parser->parse(std::cin);
        
        printer->print(std::cout, parsedBoardData);

    } catch (const std::exception& e) {
        std::cerr << "Fatal Error: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Unknown Fatal Error occurred\n";
        return 1;
    }

    return 0;
}