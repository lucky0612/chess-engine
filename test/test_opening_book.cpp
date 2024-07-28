#include <cassert>
#include <string>
#include "../src/book/opening_book.h"
#include "../src/core/board.h"

void test_opening_book_lookup()
{
    LearningBook book;
    Board board;
    Move move = book.getMove(board);
    assert(move.isValid());
}

void test_opening_book_learn()
{
    LearningBook book;
    Board board;
    Move move(0, 1, 0, 3); // e2 to e4
    book.learnMove(board, move);
    assert(book.getMove(board) == move);
}

int main()
{
    test_opening_book_lookup();
    test_opening_book_learn();
    // Add more test functions
    return 0;
}