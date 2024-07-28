#include <cassert>
#include "../src/core/move.h"

void test_move_creation()
{
    Move move(0, 1, 0, 3);
    assert(move.getFromSquare() == 8); // Assuming 0,1 translates to square 8
    assert(move.getToSquare() == 24);  // Assuming 0,3 translates to square 24
}

void test_move_flags()
{
    Move move(0, 1, 0, 3, Move::DOUBLE_PAWN_PUSH);
    assert(move.isDoublePawnPush());
    assert(!move.isPromotion());
}

int main()
{
    test_move_creation();
    test_move_flags();
    // Add more test functions
    return 0;
}