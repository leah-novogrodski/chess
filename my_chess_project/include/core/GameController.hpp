#pragma once
#include <iostream>
#include "GameEngine.hpp"

namespace core {
    class GameController {
    public:
        static void processCommands(std::istream& in, std::ostream& out, GameEngine& engine);
    };
}