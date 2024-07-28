#include "futility_pruning.h"
#include "../evaluation/evaluation.h" // Assume you have an evaluation function

namespace ChessEngine
{

    FutilityPruning::FutilityPruning(int margin) : margin(margin) {}

    bool FutilityPruning::should_prune(const Board &board, int depth, int alpha, int beta) const
    {
        if (depth >= 3 || board.is_in_check(board.side_to_move()))
        {
            return false;
        }

        int static_eval = Evaluation::evaluate(board);

        if (depth == 1 && static_eval + margin <= alpha)
        {
            return true;
        }

        if (depth == 2 && static_eval + margin * 2 <= alpha)
        {
            return true;
        }

        return false;
    }

    void FutilityPruning::set_margin(int margin)
    {
        this->margin = margin;
    }

    int FutilityPruning::evaluate_move(const Board &board, const Move &move) const
    {
        // This is a simple move evaluation. You might want to implement a more sophisticated one.
        int score = 0;

        // Capturing moves
        if (board.is_capture(move))
        {
            Piece captured = board.piece_at(move.to());
            Piece attacker = board.piece_at(move.from());
            score += Evaluation::get_piece_value(captured) - Evaluation::get_piece_value(attacker) / 10;
        }

        // Promotions
        if (move.is_promotion())
        {
            score += Evaluation::get_piece_value(move.promotion_piece());
        }

        // You can add more evaluation criteria here

        return score;
    }

} // namespace ChessEngine