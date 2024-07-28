#include <iostream>
#include <memory>
#include <string>
#include "core/board.h"
#include "engine/search.h"
#include "engine/evaluation.h"
#include "engine/mcts.h"
#include "ai/neuralnet.h"
#include "utils/bitboard.h"
#include "utils/time_manager.h"
#include "book/opening_book.h"
#include "book/endgame_tablebase.h"
#include "uci/uci.h"
#include "learning/opponent_model.h"
#include "learning/meta_learning.h"

int main(int argc, char *argv[])
{
    std::cout << "AdvancedMCTS Chess Engine" << std::endl;

    // Initialize components
    auto board = std::make_unique<Board>();
    auto bitboard = std::make_unique<HybridBitboard>();
    auto evaluation = std::make_unique<AdaptiveNN>();
    auto search = std::make_unique<DynamicPruning>();
    auto mcts = std::make_unique<AdvancedMCTS>();
    auto openingBook = std::make_unique<LearningBook>();
    auto endgameTablebase = std::make_unique<HybridTablebase>();
    auto timeManager = std::make_unique<AdaptiveClock>();
    auto opponentModel = std::make_unique<StyleAdapt>();
    auto metaLearning = std::make_unique<HeuristicOptimizer>();

    // Initialize UCI interface
    UCI uci(board.get(), search.get(), evaluation.get(), mcts.get(),
            openingBook.get(), endgameTablebase.get(), timeManager.get(),
            opponentModel.get(), metaLearning.get());

    // Main loop
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line == "quit")
        {
            break;
        }

        uci.processCommand(line);
    }

    // Cleanup and save learned data
    openingBook->save();
    metaLearning->saveParameters();

    std::cout << "Engine shutting down. Goodbye!" << std::endl;
    return 0;
}