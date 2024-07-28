#include <cassert>
#include <sstream>
#include "../src/uci/uci.h"
#include "../src/core/board.h"

void test_uci_position_command()
{
    Board board;
    DynamicPruning search;
    AdaptiveNN evaluation;
    AdvancedMCTS mcts;
    LearningBook openingBook;
    HybridTablebase endgameTablebase;
    AdaptiveClock timeManager;
    StyleAdapt opponentModel;
    HeuristicOptimizer metaLearning;

    UCI uci(&board, &search, &evaluation, &mcts, &openingBook, &endgameTablebase,
            &timeManager, &opponentModel, &metaLearning);

    std::istringstream iss("position startpos moves e2e4 e7e5");
    uci.processCommand(iss.str());

    assert(board.getPiece(4, 3) == Piece::WHITE_PAWN);
    assert(board.getPiece(4, 4) == Piece::BLACK_PAWN);
}

void test_uci_go_command()
{
    Board board;
    DynamicPruning search;
    AdaptiveNN evaluation;
    AdvancedMCTS mcts;
    LearningBook openingBook;
    HybridTablebase endgameTablebase;
    AdaptiveClock timeManager;
    StyleAdapt opponentModel;
    HeuristicOptimizer metaLearning;

    UCI uci(&board, &search, &evaluation, &mcts, &openingBook, &endgameTablebase,
            &timeManager, &opponentModel, &metaLearning);

    std::istringstream iss("go depth 4");
    uci.processCommand(iss.str());
    // In a real test, you'd need to capture the output and verify it
}

int main()
{
    test_uci_position_command();
    test_uci_go_command();
    // Add more test functions
    return 0;
}