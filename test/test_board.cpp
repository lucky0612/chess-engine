#include <cassert>
#include "../src/core/board.h"

void test_board_initialization()
{
    Board board;
    assert(board.getPiece(0, 0) == Piece::WHITE_ROOK);
    assert(board.getPiece(4, 7) == Piece::BLACK_KING);
    // Add more assertions for initial board state
}

void test_board_move()
{
    Board board;
    Move move(0, 1, 0, 3); // e2 to e4
    board.makeMove(move);
    assert(board.getPiece(0, 3) == Piece::WHITE_PAWN);
    assert(board.getPiece(0, 1) == Piece::EMPTY);
}

int main()
{
    test_board_initialization();
    test_board_move();
    // Add more test functions
    return 0;
}