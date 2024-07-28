#ifndef NULL_MOVE_H
#define NULL_MOVE_H

#include "../core/board.h"
#include "../core/types.h"

namespace ChessEngine
{

    class NullMovePruning
    {
    public:
        NullMovePruning(int R = 3);

        bool should_apply(const Board &board, int depth, int beta) const;
        int get_reduced_depth(int depth) const;

        void set_reduction_factor(int R);

    private:
        int R; // Reduction factor

        bool is_endgame(const Board &board) const;
        bool is_in_check(const Board &board) const;
        bool has_non_pawn_material(const Board &board, Color side) const;
    };

} // namespace ChessEngine

#endif // NULL_MOVE_H