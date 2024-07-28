#ifndef OPPONENT_MODEL_H
#define OPPONENT_MODEL_H

#include <vector>
#include <unordered_map>
#include "../core/types.h"
#include "../core/move.h"
#include "../core/board.h"

namespace ChessEngine
{

    class OpponentModel
    {
    public:
        OpponentModel();

        void update_model(const Board &board, const Move &move);
        void adjust_evaluation(int &eval, const Board &board);
        void reset();

        // Getter methods for model parameters
        double get_aggression() const;
        double get_positional_preference() const;
        double get_opening_preference(const std::string &opening) const;

    private:
        static constexpr int HISTORY_SIZE = 50;

        std::vector<Move> move_history;
        std::unordered_map<std::string, int> opening_choices;

        double aggression;
        double positional_preference;

        void update_aggression(const Board &board, const Move &move);
        void update_positional_preference(const Board &board, const Move &move);
        void update_opening_preference(const Board &board);

        std::string identify_opening(const Board &board) const;
    };

} // namespace ChessEngine

#endif // OPPONENT_MODEL_H