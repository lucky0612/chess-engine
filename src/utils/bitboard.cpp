#include "bitboard.h"
#include <bit>

namespace ChessEngine
{

    Bitboard BitboardUtils::set_bit(Bitboard bb, Square sq)
    {
        return bb | (1ULL << sq);
    }

    Bitboard BitboardUtils::clear_bit(Bitboard bb, Square sq)
    {
        return bb & ~(1ULL << sq);
    }

    bool BitboardUtils::is_bit_set(Bitboard bb, Square sq)
    {
        return (bb & (1ULL << sq)) != 0;
    }

    int BitboardUtils::pop_count(Bitboard bb)
    {
        return std::popcount(bb);
    }

    Square BitboardUtils::bitscan_forward(Bitboard bb)
    {
        return static_cast<Square>(std::countr_zero(bb));
    }

    Square BitboardUtils::bitscan_reverse(Bitboard bb)
    {
        return static_cast<Square>(63 - std::countl_zero(bb));
    }

    Bitboard BitboardUtils::north_one(Bitboard bb)
    {
        return bb << 8;
    }

    Bitboard BitboardUtils::south_one(Bitboard bb)
    {
        return bb >> 8;
    }

    Bitboard BitboardUtils::east_one(Bitboard bb)
    {
        return (bb & ~FILE_H) << 1;
    }

    Bitboard BitboardUtils::west_one(Bitboard bb)
    {
        return (bb & ~FILE_A) >> 1;
    }

    Bitboard BitboardUtils::north_east_one(Bitboard bb)
    {
        return (bb & ~FILE_H) << 9;
    }

    Bitboard BitboardUtils::north_west_one(Bitboard bb)
    {
        return (bb & ~FILE_A) << 7;
    }

    Bitboard BitboardUtils::south_east_one(Bitboard bb)
    {
        return (bb & ~FILE_H) >> 7;
    }

    Bitboard BitboardUtils::south_west_one(Bitboard bb)
    {
        return (bb & ~FILE_A) >> 9;
    }

    Bitboard BitboardUtils::fill_north(Bitboard bb)
    {
        bb |= (bb << 8);
        bb |= (bb << 16);
        bb |= (bb << 32);
        return bb;
    }

    Bitboard BitboardUtils::fill_south(Bitboard bb)
    {
        bb |= (bb >> 8);
        bb |= (bb >> 16);
        bb |= (bb >> 32);
        return bb;
    }

    Bitboard BitboardUtils::fill_east(Bitboard bb)
    {
        const Bitboard k1 = ~FILE_A;
        bb |= k1 & (bb << 1);
        bb |= k1 & (bb << 2);
        bb |= k1 & (bb << 4);
        return bb;
    }

    Bitboard BitboardUtils::fill_west(Bitboard bb)
    {
        const Bitboard k1 = ~FILE_H;
        bb |= k1 & (bb >> 1);
        bb |= k1 & (bb >> 2);
        bb |= k1 & (bb >> 4);
        return bb;
    }

} // namespace ChessEngine