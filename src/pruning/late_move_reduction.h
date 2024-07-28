#ifndef LATE_MOVE_REDUCTION_H
#define LATE_MOVE_REDUCTION_H

#include "../core/types.h"
#include "../core/move.h"

namespace ChessEngine
{

    class LateMoveReduction
    {
    public:
        LateMoveReduction(int full_depth_moves = 4, int reduction_limit = 3);

        bool should_reduce(int depth, int move_number) const;
        int get_reduction(int depth, int move_number) const;

        void set_full_depth_moves(int moves);
        void set_reduction_limit(int limit);

    private:
        int full_depth_moves;
        int reduction_limit;
    };

} // namespace ChessEngine

#endif // LATE_MOVE_REDUCTION_H