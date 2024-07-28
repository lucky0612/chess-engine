#ifndef META_LEARNING_H
#define META_LEARNING_H

#include <vector>
#include <unordered_map>
#include "../core/types.h"
#include "../core/board.h"
#include "../engine/search.h"

namespace ChessEngine
{

    class MetaLearning
    {
    public:
        MetaLearning(Search &search);

        void update_from_game(const std::vector<Move> &moves, GameResult result);
        void optimize_parameters();
        void reflect_on_game(const std::vector<Move> &moves, GameResult result);

    private:
        Search &search;
        std::unordered_map<std::string, double> parameters;
        std::vector<std::pair<std::vector<Move>, GameResult>> game_history;

        void update_evaluation_weights(const std::vector<Move> &moves, GameResult result);
        void update_search_parameters(const std::vector<Move> &moves, GameResult result);
        void generalize_concepts(const std::vector<Move> &moves, GameResult result);

        double calculate_parameter_impact(const std::string &param_name);
    };

} // namespace ChessEngine

#endif // META_LEARNING_H