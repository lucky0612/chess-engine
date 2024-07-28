#include <cassert>
#include "../src/utils/bitboard.h"

void test_bitboard_set_get()
{
    HybridBitboard bb;
    bb.setPiece(0, 0, Piece::WHITE_ROOK);
    assert(bb.getPiece(0, 0) == Piece::WHITE_ROOK);
}

void test_bitboard_move()
{
    HybridBitboard bb;
    bb.setPiece(0, 1, Piece::WHITE_PAWN);
    bb.movePiece(0, 1, 0, 3);
    assert(bb.getPiece(0, 3) == Piece::WHITE_PAWN);
    assert(bb.getPiece(0, 1) == Piece::EMPTY);
}

int main()
{
    test_bitboard_set_get();
    test_bitboard_move();
    // Add more test functions
    return 0;
}