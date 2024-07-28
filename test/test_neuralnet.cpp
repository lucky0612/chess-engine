#include <cassert>
#include "../src/ai/neuralnet.h"
#include "../src/core/board.h"

void test_neuralnet_output()
{
    Board board;
    AdaptiveNN nn;
    float output = nn.evaluate(board);
    assert(output >= -1.0f && output <= 1.0f);
}

void test_neuralnet_incremental_update()
{
    Board board;
    AdaptiveNN nn;
    float initial = nn.evaluate(board);
    Move move(0, 1, 0, 3); // e2 to e4
    board.makeMove(move);
    nn.incrementalUpdate(board, move);
    float after = nn.evaluate(board);
    assert(initial != after);
}

int main()
{
    test_neuralnet_output();
    test_neuralnet_incremental_update();
    // Add more test functions
    return 0;
}