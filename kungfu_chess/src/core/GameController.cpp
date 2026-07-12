#include "../../include/core/GameController.hpp"
#include <string>
#include <sstream>

namespace core {
    void GameController::processCommands(std::istream& in, std::ostream& out, GameEngine& engine) {
        std::string line;
        while (std::getline(in, line)) {
            if (line.empty()) continue;

            std::istringstream iss(line);
            std::string cmd;
            iss >> cmd;

            if (cmd == "click") {
                int x, y;
                if (iss >> x >> y) {
                    engine.click(x, y);
                }
            } 
            else if (cmd == "wait") {
                int ms;
                if (iss >> ms) {
                    engine.wait(ms);
                }
            } 
            else if (cmd == "print") {
                std::string arg;
                if (iss >> arg && arg == "board") {
                    engine.printBoard(out);
                }
            }
        }
    }
}