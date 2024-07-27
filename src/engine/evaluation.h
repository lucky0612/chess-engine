#pragma once

#include "../core/board.h"

namespace ChessEngine
{

    class Evaluation
    {
    public:
        static int evaluate(const Board &board);

    private:
        static int evaluateMaterial(const Board &board);
        static int evaluatePosition(const Board &board);
        static int evaluatePawnStructure(const Board &board);
        static int evaluateKingSafety(const Board &board);
    };

} // namespace ChessEngine