#include <iostream>
#include "../src/core/board.h"
#include "../src/engine/search.h"
#include "../src/uci/uci.h"

int main()
{
    // Initialize the board with the starting position
    Board board;

    // Create a search object
    DynamicPruning search;

    // Set up UCI
    UCI uci(&board, &search);

    // Example of making a move
    Move move = Move(Square::E2, Square::E4);
    board.makeMove(move);

    std::cout << "Board after 1.e4:\n"
              << board.toFEN() << std::endl;

    // Example of searching for the best move
    SearchLimits limits;
    limits.depth = 6;
    Move bestMove = search.getBestMove(board, limits);

    std::cout << "Best move found: " << bestMove.toUCI() << std::endl;

    // Example of UCI command
    uci.processCommand("position startpos moves e2e4");
    uci.processCommand("go depth 6");

    return 0;
}