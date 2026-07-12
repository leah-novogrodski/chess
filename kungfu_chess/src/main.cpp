
#include "Board.hpp"
#include "GameEngine.hpp"
#include "GameController.hpp"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        core::Board board = core::Board::parse(std::cin);
        core::GameEngine engine(board);
        core::GameController::processCommands(std::cin, std::cout, engine);
        
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
        return 1;
    }

    return 0;
}