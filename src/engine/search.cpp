#include "search.h"
#include "evaluation.h"
#include <algorithm>
#include <limits>

namespace ChessEngine
{

    Search::Search(Board &board) : board_(board), nodesSearched_(0) {}

    Move Search::findBestMove(int depth, std::chrono::milliseconds timeLimit)
    {
        auto startTime = std::chrono::steady_clock::now();
        nodesSearched_ = 0;
        Move bestMove;
        int bestScore = std::numeric_limits<int>::min();

        std::vector<Move> legalMoves = board_.generateLegalMoves();
        orderMoves(legalMoves);

        for (const auto &move : legalMoves)
        {
            board_.makeMove(move);
            int score = -alphaBeta(depth - 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), false);
            board_.undoMove(move);

            if (score > bestScore)
            {
                bestScore = score;
                bestMove = move;
            }

            if (isTimeUp(startTime, timeLimit))
            {
                break;
            }
        }

        return bestMove;
    }

    int Search::alphaBeta(int depth, int alpha, int beta, bool maximizingPlayer)
    {
        if (depth == 0 || board_.isCheckmate() || board_.isStalemate())
        {
            return Evaluation::evaluate(board_);
        }

        nodesSearched_++;

        std::vector<Move> legalMoves = board_.generateLegalMoves();
        orderMoves(legalMoves);

        if (maximizingPlayer)
        {
            int maxEval = std::numeric_limits<int>::min();
            for (const auto &move : legalMoves)
            {
                board_.makeMove(move);
                int eval = alphaBeta(depth - 1, alpha, beta, false);
                board_.undoMove(move);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha)
                {
                    break;
                }
            }
            return maxEval;
        }
        else
        {
            int minEval = std::numeric_limits<int>::max();
            for (const auto &move : legalMoves)
            {
                board_.makeMove(move);
                int eval = alphaBeta(depth - 1, alpha, beta, true);
                board_.undoMove(move);
                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha)
                {
                    break;
                }
            }
            return minEval;
        }
    }

    bool Search::isTimeUp(const std::chrono::time_point<std::chrono::steady_clock> &startTime,
                          const std::chrono::milliseconds &timeLimit) const
    {
        auto currentTime = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime) >= timeLimit;
    }

    void Search::orderMoves(std::vector<Move> &moves)
    {
        // Implement move ordering here
        // This is a placeholder implementation
        std::sort(moves.begin(), moves.end(), [](const Move &a, const Move &b)
                  {
        // Add your move ordering logic here
        return false; });
    }

} // namespace ChessEngine