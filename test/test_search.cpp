#include <cassert>
#include "../src/engine/search.h"
#include "../src/core/board.h"

void test_search_depth()
{
    Board board;
    DynamicPruning search;
    Move bestMove = search.findBestMove(board, 4); // Search to depth 4
    assert(bestMove.isValid());                    // Just check if a valid move is returned
}

void test_search_time()
{
    Board board;
    DynamicPruning search;
    Move bestMove = search.findBestMoveTime(board, 1000); // Search for 1 second
    assert(bestMove.isValid());
}

int main()
{
    test_search_depth();
    test_search_time();
    // Add more test functions
    return 0;
}