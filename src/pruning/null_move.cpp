#include "null_move.h"

namespace ChessEngine
{

    NullMovePruning::NullMovePruning(int R) : R(R) {}

    bool NullMovePruning::should_apply(const Board &board, int depth, int beta) const
    {
        return depth >= R + 1 &&
               !is_endgame(board) &&
               !is_in_check(board) &&
               has_non_pawn_material(board, board.side_to_move());
    }

    int NullMovePruning::get_reduced_depth(int depth) const
    {
        return depth - R - 1;
    }

    void NullMovePruning::set_reduction_factor(int R)
    {
        this->R = R;
    }

    bool NullMovePruning::is_endgame(const Board &board) const
    {
        // Simple endgame detection: check if both sides have less than 13 points of material
        return board.get_material_count(Color::WHITE) < 13 &&
               board.get_material_count(Color::BLACK) < 13;
    }

    bool NullMovePruning::is_in_check(const Board &board) const
    {
        return board.is_in_check(board.side_to_move());
    }

    bool NullMovePruning::has_non_pawn_material(const Board &board, Color side) const
    {
        return board.get_pieces(KNIGHT, side) | board.get_pieces(BISHOP, side) |
               board.get_pieces(ROOK, side) | board.get_pieces(QUEEN, side);
    }

} // namespace ChessEngine