#ifndef FUTILITY_PRUNING_H
#define FUTILITY_PRUNING_H

#include "../core/board.h"
#include "../core/types.h"

namespace ChessEngine
{

    class FutilityPruning
    {
    public:
        FutilityPruning(int margin = 200);

        bool should_prune(const Board &board, int depth, int alpha, int beta) const;

        void set_margin(int margin);

    private:
        int margin;

        int evaluate_move(const Board &board, const Move &move) const;
    };

} // namespace ChessEngine

#endif // FUTILITY_PRUNING_H