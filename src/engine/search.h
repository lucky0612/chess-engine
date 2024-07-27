#pragma once

#include "../core/board.h"
#include "../core/move.h"
#include <chrono>

namespace ChessEngine
{

    class Search
    {
    public:
        Search(Board &board);
        Move findBestMove(int depth, std::chrono::milliseconds timeLimit);

    private:
        Board &board_;
        int nodesSearched_;

        int alphaBeta(int depth, int alpha, int beta, bool maximizingPlayer);
        bool isTimeUp(const std::chrono::time_point<std::chrono::steady_clock> &startTime,
                      const std::chrono::milliseconds &timeLimit) const;
        void orderMoves(std::vector<Move> &moves);
    };

} // namespace ChessEngine