#pragma once

#include "../core/board.h"
#include "../core/move.h"
#include <memory>
#include <vector>

namespace ChessEngine
{

    class MCTSNode
    {
    public:
        MCTSNode(Board &board, Move move, MCTSNode *parent);
        void expand();
        MCTSNode *select();
        void backpropagate(double result);
        bool isFullyExpanded() const;
        bool isLeaf() const;
        double getUCB1(double C) const;

    private:
        Board board_;
        Move move_;
        MCTSNode *parent_;
        std::vector<std::unique_ptr<MCTSNode>> children_;
        int visits_;
        double totalScore_;
    };

    class MCTS
    {
    public:
        MCTS(Board &board, std::chrono::milliseconds timeLimit);
        Move findBestMove();

    private:
        Board &board_;
        std::chrono::milliseconds timeLimit_;
        std::unique_ptr<MCTSNode> root_;

        MCTSNode *selectNode(MCTSNode *node);
        double simulate(Board &board);
        bool isTimeUp(const std::chrono::time_point<std::chrono::steady_clock> &startTime) const;
    };

} // namespace ChessEngine