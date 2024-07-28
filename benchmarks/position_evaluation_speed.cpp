#include <chrono>
#include <iostream>
#include <vector>
#include "../src/core/board.h"
#include "../src/engine/evaluation.h"

const int NUM_POSITIONS = 1000000;

std::vector<Board> generateRandomPositions(int count)
{
    std::vector<Board> positions;
    for (int i = 0; i < count; ++i)
    {
        Board board;
        // Make some random moves
        for (int j = 0; j < 10; ++j)
        {
            auto moves = board.generateLegalMoves();
            if (moves.empty())
                break;
            board.makeMove(moves[rand() % moves.size()]);
        }
        positions.push_back(board);
    }
    return positions;
}

int main()
{
    AdaptiveNN eval;
    auto positions = generateRandomPositions(NUM_POSITIONS);

    auto start = std::chrono::high_resolution_clock::now();

    for (const auto &position : positions)
    {
        eval.evaluate(position);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Evaluated " << NUM_POSITIONS << " positions in " << duration.count() << " ms" << std::endl;
    std::cout << "Positions per second: " << (NUM_POSITIONS * 1000.0 / duration.count()) << std::endl;

    return 0;
}