#pragma once

#include "../core/board.h"
#include "neuralnet.h"
#include <vector>

namespace ChessEngine
{

    class SelfPlay
    {
    public:
        SelfPlay(NeuralNetwork &network);
        std::vector<std::pair<Board, float>> generateGames(int numGames);

    private:
        NeuralNetwork &network;
        std::pair<Board, float> playGame();
        Move getBestMove(const Board &board);
    };

} // namespace ChessEngine