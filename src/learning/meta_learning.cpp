#include "meta_learning.h"
#include "../evaluation/evaluation.h"
#include <algorithm>
#include <random>

namespace ChessEngine
{

    MetaLearning::MetaLearning(Search &search) : search(search)
    {
        // Initialize parameters with default values
        parameters["piece_values.pawn"] = 100;
        parameters["piece_values.knight"] = 320;
        parameters["piece_values.bishop"] = 330;
        parameters["piece_values.rook"] = 500;
        parameters["piece_values.queen"] = 900;
        parameters["search.null_move_reduction"] = 3;
        parameters["search.futility_margin"] = 200;
        parameters["search.lmr_full_depth_moves"] = 4;
    }

    void MetaLearning::update_from_game(const std::vector<Move> &moves, GameResult result)
    {
        game_history.emplace_back(moves, result);
        update_evaluation_weights(moves, result);
        update_search_parameters(moves, result);
    }

    void MetaLearning::optimize_parameters()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-0.1, 0.1);

        for (auto &[param_name, value] : parameters)
        {
            double impact = calculate_parameter_impact(param_name);
            value += impact * dis(gen);
        }

        // Update the search and evaluation functions with new parameters
        search.update_parameters(parameters);
        Evaluation::update_parameters(parameters);
    }

    void MetaLearning::reflect_on_game(const std::vector<Move> &moves, GameResult result)
    {
        generalize_concepts(moves, result);
    }

    void MetaLearning::update_evaluation_weights(const std::vector<Move> &moves, GameResult result)
    {
        // This is a simplified example. In a real implementation, you would analyze
        // the game more deeply to determine how to adjust evaluation weights.
        if (result == GameResult::WIN)
        {
            parameters["piece_values.pawn"] *= 1.01;
            parameters["piece_values.knight"] *= 1.01;
            parameters["piece_values.bishop"] *= 1.01;
            parameters["piece_values.rook"] *= 1.01;
            parameters["piece_values.queen"] *= 1.01;
        }
        else if (result == GameResult::LOSS)
        {
            parameters["piece_values.pawn"] *= 0.99;
            parameters["piece_values.knight"] *= 0.99;
            parameters["piece_values.bishop"] *= 0.99;
            parameters["piece_values.rook"] *= 0.99;
            parameters["piece_values.queen"] *= 0.99;
        }
    }

    void MetaLearning::update_search_parameters(const std::vector<Move> &moves, GameResult result)
    {
        // This is a simplified example. In a real implementation, you would analyze
        // the effectiveness of search techniques during the game.
        if (result == GameResult::WIN)
        {
            parameters["search.null_move_reduction"] *= 1.01;
            parameters["search.futility_margin"] *= 1.01;
            parameters["search.lmr_full_depth_moves"] *= 0.99;
        }
        else if (result == GameResult::LOSS)
        {
            parameters["search.null_move_reduction"] *= 0.99;
            parameters["search.futility_margin"] *= 0.99;
            parameters["search.lmr_full_depth_moves"] *= 1.01;
        }
    }

    void MetaLearning::generalize_concepts(const std::vector<Move> &moves, GameResult result)
    {
        // This is a placeholder for a more complex concept generalization system.
        // In a real implementation, you might look for recurring patterns in successful games
        // and try to formulate general strategic or tactical rules.
    }

    double MetaLearning::calculate_parameter_impact(const std::string &param_name)
    {
        // This is a placeholder for a more sophisticated impact calculation.
        // In a real implementation, you might use techniques like ANOVA or
        // regression analysis to determine the impact of each parameter.
        return 0.0;
    }

} // namespace ChessEngine