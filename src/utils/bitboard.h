#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include "../core/types.h"

namespace ChessEngine
{

    using Bitboard = uint64_t;

    class BitboardUtils
    {
    public:
        static Bitboard set_bit(Bitboard bb, Square sq);
        static Bitboard clear_bit(Bitboard bb, Square sq);
        static bool is_bit_set(Bitboard bb, Square sq);
        static int pop_count(Bitboard bb);
        static Square bitscan_forward(Bitboard bb);
        static Square bitscan_reverse(Bitboard bb);

        // Shift operations
        static Bitboard north_one(Bitboard bb);
        static Bitboard south_one(Bitboard bb);
        static Bitboard east_one(Bitboard bb);
        static Bitboard west_one(Bitboard bb);
        static Bitboard north_east_one(Bitboard bb);
        static Bitboard north_west_one(Bitboard bb);
        static Bitboard south_east_one(Bitboard bb);
        static Bitboard south_west_one(Bitboard bb);

        // Utility functions
        static Bitboard fill_north(Bitboard bb);
        static Bitboard fill_south(Bitboard bb);
        static Bitboard fill_east(Bitboard bb);
        static Bitboard fill_west(Bitboard bb);

        // Constants
        static const Bitboard FULL_BOARD = 0xFFFFFFFFFFFFFFFFULL;
        static const Bitboard EMPTY_BOARD = 0ULL;
        static const Bitboard FILE_A = 0x0101010101010101ULL;
        static const Bitboard FILE_H = 0x8080808080808080ULL;
        static const Bitboard RANK_1 = 0x00000000000000FFULL;
        static const Bitboard RANK_8 = 0xFF00000000000000ULL;
    };

} // namespace ChessEngine

#endif // BITBOARD_H