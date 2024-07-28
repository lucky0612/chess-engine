#include "late_move_reduction.h"
#include <algorithm>
#include <cmath>

namespace ChessEngine
{

    LateMoveReduction::LateMoveReduction(int full_depth_moves, int reduction_limit)
        : full_depth_moves(full_depth_moves), reduction_limit(reduction_limit) {}

    bool LateMoveReduction::should_reduce(int depth, int move_number) const
    {
        return depth >= 3 && move_number > full_depth_moves;
    }

    int LateMoveReduction::get_reduction(int depth, int move_number) const
    {
        if (!should_reduce(depth, move_number))
        {
            return 0;
        }

        // Calculate reduction based on depth and move number
        int reduction = 1 + std::log(depth) * std::log(move_number) / 2.5;

        // Limit the reduction
        return std::min(reduction, reduction_limit);
    }

    void LateMoveReduction::set_full_depth_moves(int moves)
    {
        full_depth_moves = moves;
    }

    void LateMoveReduction::set_reduction_limit(int limit)
    {
        reduction_limit = limit;
    }

} // namespace ChessEngine