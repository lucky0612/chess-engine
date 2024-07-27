#include "selfplay.h"
#include <random>
#include <algorithm>

namespace ChessEngine
{

    SelfPlay::SelfPlay(NeuralNetwork &network) : network(network) {}

    std::vector<std::pair<Board, float>> SelfPlay::generateGames(int numGames)
    {
        std::vector<std::pair<Board, float>> games;
        for (int i = 0; i < numGames; ++i)
        {
            games.push_back(playGame());
        }
        return games;
    }

    std::pair<Board, float> SelfPlay::playGame()
    {
        Board board;
        std::vector<Board> gamePositions;

        while (!board.isCheckmate() && !board.isStalemate())
        {
            gamePositions.push_back(board);
            Move bestMove = getBestMove(board);
            board.makeMove(bestMove);
        }

        float result;
        if (board.isCheckmate())
        {
            result = (board.sideToMove() == Color::WHITE) ? 0.0f : 1.0f;
        }
        else
        {
            result = 0.5f;
        }

        return {gamePositions[rand() % gamePositions.size()], result};
    }

    Move SelfPlay::getBestMove(const Board &board)
    {
        auto legalMoves = board.generateLegalMoves();
        std::vector<std::pair<Move, float>> moveScores;

        for (const auto &move : legalMoves)
        {
            Board newBoard = board;
            newBoard.makeMove(move);
            float score = network.evaluate(newBoard);
            moveScores.emplace_back(move, score);
        }

        // Choose move with highest score
        auto bestMove = std::max_element(moveScores.begin(), moveScores.end(),
                                         [](const auto &a, const auto &b)
                                         { return a.second < b.second; });

        return bestMove->first;
    }

} // namespace ChessEngine