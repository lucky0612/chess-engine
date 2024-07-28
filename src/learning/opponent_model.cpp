#include "opponent_model.h"
#include "../evaluation/evaluation.h"
#include <algorithm>

namespace ChessEngine
{

    OpponentModel::OpponentModel()
        : aggression(0.5), positional_preference(0.5) {}

    void OpponentModel::update_model(const Board &board, const Move &move)
    {
        if (move_history.size() >= HISTORY_SIZE)
        {
            move_history.erase(move_history.begin());
        }
        move_history.push_back(move);

        update_aggression(board, move);
        update_positional_preference(board, move);
        update_opening_preference(board);
    }

    void OpponentModel::adjust_evaluation(int &eval, const Board &board)
    {
        // Adjust evaluation based on opponent's style
        eval = static_cast<int>(eval * (1.0 + (aggression - 0.5) * 0.1));
        eval = static_cast<int>(eval * (1.0 + (positional_preference - 0.5) * 0.1));

        // Adjust for opening preference
        std::string opening = identify_opening(board);
        if (!opening.empty())
        {
            double pref = get_opening_preference(opening);
            eval = static_cast<int>(eval * (1.0 + (pref - 0.5) * 0.05));
        }
    }

    void OpponentModel::reset()
    {
        move_history.clear();
        opening_choices.clear();
        aggression = 0.5;
        positional_preference = 0.5;
    }

    double OpponentModel::get_aggression() const
    {
        return aggression;
    }

    double OpponentModel::get_positional_preference() const
    {
        return positional_preference;
    }

    double OpponentModel::get_opening_preference(const std::string &opening) const
    {
        int total_openings = 0;
        for (const auto &[_, count] : opening_choices)
        {
            total_openings += count;
        }

        auto it = opening_choices.find(opening);
        if (it != opening_choices.end() && total_openings > 0)
        {
            return static_cast<double>(it->second) / total_openings;
        }
        return 0.5; // Default to neutral preference
    }

    void OpponentModel::update_aggression(const Board &board, const Move &move)
    {
        if (board.is_capture(move))
        {
            aggression = std::min(1.0, aggression + 0.05);
        }
        else
        {
            aggression = std::max(0.0, aggression - 0.01);
        }
    }

    void OpponentModel::update_positional_preference(const Board &board, const Move &move)
    {
        int before = Evaluation::evaluate_position(board);
        Board after_board = board;
        after_board.make_move(move);
        int after = Evaluation::evaluate_position(after_board);

        if (after > before)
        {
            positional_preference = std::min(1.0, positional_preference + 0.05);
        }
        else
        {
            positional_preference = std::max(0.0, positional_preference - 0.01);
        }
    }

    void OpponentModel::update_opening_preference(const Board &board)
    {
        std::string opening = identify_opening(board);
        if (!opening.empty())
        {
            opening_choices[opening]++;
        }
    }

    std::string OpponentModel::identify_opening(const Board &board) const
    {
        // This is a placeholder. In a real implementation, you would have a database
        // of opening positions and their names, and you would match the current board
        // state against this database.
        return "";
    }

} // namespace ChessEngine