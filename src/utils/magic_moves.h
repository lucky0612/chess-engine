#ifndef MAGIC_MOVES_H
#define MAGIC_MOVES_H

#include "bitboard.h"
#include "../core/types.h"

namespace ChessEngine
{

    class MagicMoves
    {
    public:
        MagicMoves();

        Bitboard get_rook_moves(Square sq, Bitboard occupancy) const;
        Bitboard get_bishop_moves(Square sq, Bitboard occupancy) const;

    private:
        struct MagicEntry
        {
            Bitboard mask;
            Bitboard magic;
            Bitboard *moves;
            int shift;
        };

        MagicEntry rook_table[64];
        MagicEntry bishop_table[64];

        void initialize_magic_tables();
        Bitboard find_magic_number(Square sq, bool is_rook);
        Bitboard generate_occupancy(int index, Bitboard mask) const;
    };

} // namespace ChessEngine

#endif // MAGIC_MOVES_H