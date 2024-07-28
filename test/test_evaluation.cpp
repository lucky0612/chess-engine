#include <cassert>
#include "../src/engine/evaluation.h"
#include "../src/core/board.h"

void test_evaluation_initial_position()
{
    Board board;
    AdaptiveNN evaluation;
    int score = evaluation.evaluate(board);
    assert(score == 0); // Initial position should be equal
}

void test_evaluation_material_difference()
{
    Board board;
    board.removePiece(0, 7); // Remove a black rook
    AdaptiveNN evaluation;
    int score = evaluation.evaluate(board);
    assert(score > 0); // White should be winning
}

int main()
{
    test_evaluation_initial_position();
    test_evaluation_material_difference();
    // Add more test functions
    return 0;
}