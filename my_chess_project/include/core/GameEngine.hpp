#pragma once
#include "Board.hpp"
#include <cstdint>

namespace core {
    class GameEngine {
    public:
        explicit GameEngine(const Board& initialBoard);

        void click(int x, int y);
        void wait(int ms);
        void printBoard(std::ostream& out) const;

        bool hasActiveSelection() const;
        uint64_t getClockMs() const;
        const Board& getBoard() const;

    private:
        Board board;
        uint64_t clockMs;
        
        bool hasSelection;
        int selectedRow;
        int selectedCol;

        static constexpr int CELL_SIZE = 100; 
    };
}