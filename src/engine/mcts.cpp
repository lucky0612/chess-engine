#include "mcts.h"
#include "evaluation.h"
#include <cmath>
#include <limits>
#include <random>

namespace ChessEngine
{

    MCTSNode::MCTSNode(Board &board, Move move, MCTSNode *parent)
        : board_(board), move_(move), parent_(parent), visits_(0), totalScore_(0) {}

    void MCTSNode::expand()
    {
        auto legalMoves = board_.generateLegalMoves();
        for (const auto &move : legalMoves)
        {
            Board newBoard = board_;
            newBoard.makeMove(move);
            children_.push_back(std::make_unique<MCTSNode>(newBoard, move, this));
        }
    }

    MCTSNode *MCTSNode::select()
    {
        return *std::max_element(children_.begin(), children_.end(),
                                 [](const std::unique_ptr<MCTSNode> &a, const std::unique_ptr<MCTSNode> &b)
                                 {
                                     return a->getUCB1(sqrt(2)) < b->getUCB1(sqrt(2));
                                 });
    }

    void MCTSNode::backpropagate(double result)
    {
        visits_++;
        totalScore_ += result;
        if (parent_)
        {
            parent_->backpropagate(1 - result);
        }
    }

    bool MCTSNode::isFullyExpanded() const
    {
        return !children_.empty() && std::all_of(children_.begin(), children_.end(),
                                                 [](const std::unique_ptr<MCTSNode> &child)
                                                 { return child->visits_ > 0; });
    }

    bool MCTSNode::isLeaf() const
    {
        return children_.empty();
    }

    double MCTSNode::getUCB1(double C) const
    {
        if (visits_ == 0)
            return std::numeric_limits<double>::infinity();
        return (totalScore_ / visits_) + C * sqrt(log(parent_->visits_) / visits_);
    }

    MCTS::MCTS(Board &board, std::chrono::milliseconds timeLimit)
        : board_(board), timeLimit_(timeLimit), root_(std::make_unique<MCTSNode>(board, Move(), nullptr)) {}

    Move MCTS::findBestMove()
    {
        auto startTime = std::chrono::steady_clock::now();
        while (!isTimeUp(startTime))
        {
            MCTSNode *node = selectNode(root_.get());
            double result = simulate(node->board_);
            node->backpropagate(result);
        }

        return std::max_element(root_->children_.begin(), root_->children_.end(),
                                [](const std::unique_ptr<MCTSNode> &a, const std::unique_ptr<MCTSNode> &b)
                                {
                                    return a->visits_ < b->visits_;
                                })
            ->get()
            ->move_;
    }

    MCTSNode *MCTS::selectNode(MCTSNode *node)
    {
        while (!node->isLeaf())
        {
            if (!node->isFullyExpanded())
            {
                node->expand();
                return node->children_.back().get();
            }
            else
            {
                node = node->select();
            }
        }
        return node;
    }

    double MCTS::simulate(Board &board)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());

        while (!board.isCheckmate() && !board.isStalemate())
        {
            auto legalMoves = board.generateLegalMoves();
            std::uniform_int_distribution<> dis(0, legalMoves.size() - 1);
            board.makeMove(legalMoves[dis(gen)]);
        }

        if (board.isCheckmate())
        {
            return board.sideToMove() == Color::WHITE ? 0 : 1;
        }
        else
        {
            return 0.5;
        }
    }

    bool MCTS::isTimeUp(const std::chrono::time_point<std::chrono::steady_clock> &startTime) const
    {
        auto currentTime = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime) >= timeLimit_;
    }

} // namespace ChessEngine