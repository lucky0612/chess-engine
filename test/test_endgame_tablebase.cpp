#include <cassert>
#include "../src/book/endgame_tablebase.h"
#include "../src/core/board.h"

void test_tablebase_kpk()
{
    HybridTablebase tablebase;
    Board board;
    // Set up a King and Pawn vs King endgame
    board.clear();
    board.setPiece(0, 0, Piece::WHITE_KING);
    board.setPiece(1, 1, Piece::WHITE_PAWN);
    board.setPiece(7, 7, Piece::BLACK_KING);
    int score = tablebase.probe(board);
    assert(score > 0); // White should be winning
}

void test_tablebase_kqk()
{
    HybridTablebase tablebase;
    Board board;
    // Set up a King and Queen vs King endgame
    board.clear();
    board.setPiece(0, 0, Piece::WHITE_KING);
    board.setPiece(1, 1, Piece::WHITE_QUEEN);
    board.setPiece(7, 7, Piece::BLACK_KING);
    int score = tablebase.probe(board);
    assert(score > 0); // White should be winning
}

int main()
{
    test_tablebase_kpk();
    test_tablebase_kqk();
    // Add more test functions
    return 0;
}