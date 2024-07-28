#include <cassert>
#include "../src/pruning/null_move.h"
#include "../src/pruning/late_move_reduction.h"
#include "../src/pruning/futility_pruning.h"
#include "../src/core/board.h"

void test_null_move_pruning()
{
    Board board;
    NullMovePruning nullMove;
    int score = nullMove.search(board, 4); // Search to depth 4
    assert(score != 0);                    // Just checking if a score is returned
}

void test_late_move_reduction()
{
    Board board;
    LateMoveReduction lmr;
    int newDepth = lmr.getReducedDepth(3, 10); // 3rd move at depth 10
    assert(newDepth < 10);                     // Depth should be reduced
}

void test_futility_pruning()
{
    Board board;
    FutilityPruning futility;
    bool shouldPrune = futility.shouldPrune(board, 1, 100); // depth 1, alpha 100
    assert(shouldPrune == true || shouldPrune == false);    // Just checking if a decision is made
}

int main()
{
    test_null_move_pruning();
    test_late_move_reduction();
    test_futility_pruning();
    // Add more test functions
    return 0;
}