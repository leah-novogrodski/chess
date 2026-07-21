#pragma once

#include <optional>

#include "../engine/GameSnapshot.hpp"

namespace audio {

class GameEventDetector {
public:
    struct Events {
        bool moveStarted;
        bool captureHappened;
        bool gameOverJustNow;
    };

    Events detect(const GameSnapshot& current);

private:
    std::optional<GameSnapshot> previous;
};

}