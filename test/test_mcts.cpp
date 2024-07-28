#include <cassert>
#include "../src/engine/mcts.h"
#include "../src/core/board.h"

void test_mcts_root_expansion()
{
    Board board;
    AdvancedMCTS mcts;
    mcts.search(board, 1000); // Search for 1000 iterations
    assert(mcts.getRootNode()->getChildCount() > 0);
}

void test_mcts_best_move()
{
    Board board;
    AdvancedMCTS mcts;
    Move bestMove = mcts.getBestMove(board, 1000);
    assert(bestMove.isValid());
}

int main()
{
    test_mcts_root_expansion();
    test_mcts_best_move();
    // Add more test functions
    return 0;
}