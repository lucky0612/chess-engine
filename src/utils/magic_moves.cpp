#include "magic_moves.h"
#include <random>
#include <algorithm>

namespace ChessEngine
{

    MagicMoves::MagicMoves()
    {
        initialize_magic_tables();
    }

    void MagicMoves::initialize_magic_tables()
    {
        for (int sq = 0; sq < 64; ++sq)
        {
            rook_table[sq].magic = find_magic_number(static_cast<Square>(sq), true);
            bishop_table[sq].magic = find_magic_number(static_cast<Square>(sq), false);

            // Initialize masks and shifts
            rook_table[sq].mask =       // Generate rook mask for square sq
                bishop_table[sq].mask = // Generate bishop mask for square sq
                rook_table[sq].shift = 64 - BitboardUtils::pop_count(rook_table[sq].mask);
            bishop_table[sq].shift = 64 - BitboardUtils::pop_count(bishop_table[sq].mask);

            // Allocate and initialize move tables
            rook_table[sq].moves = new Bitboard[1 << (64 - rook_table[sq].shift)];
            bishop_table[sq].moves = new Bitboard[1 << (64 - bishop_table[sq].shift)];

            // Generate all possible occupancies and corresponding moves
            Bitboard occupancy = 0;
            do
            {
                int index = (occupancy * rook_table[sq].magic) >> rook_table[sq].shift;
                rook_table[sq].moves[index] = // Generate rook moves for this occupancy

                    index = (occupancy * bishop_table[sq].magic) >> bishop_table[sq].shift;
                bishop_table[sq].moves[index] = // Generate bishop moves for this occupancy

                    occupancy = (occupancy - rook_table[sq].mask) & rook_table[sq].mask;
            } while (occupancy);
        }
    }

    Bitboard MagicMoves::find_magic_number(Square sq, bool is_rook)
    {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint64_t> dis;

        Bitboard occupancies[4096], attacks[4096], used[4096];
        Bitboard mask = is_rook ? rook_table[sq].mask : bishop_table[sq].mask;
        int n = BitboardUtils::pop_count(mask);
        int m = 1 << n;

        for (int i = 0; i < m; i++)
        {
            occupancies[i] = generate_occupancy(i, mask);
            attacks[i] = is_rook ? // Generate rook attacks : // Generate bishop attacks
        }

        for (int k = 0; k < 100000000; k++)
        {
            Bitboard magic = dis(gen) & dis(gen) & dis(gen);
            if (BitboardUtils::pop_count((mask * magic) & 0xFF00000000000000ULL) < 6)
                continue;

            std::fill(used, used + m, 0);
            int i;
            for (i = 0; i < m; i++)
            {
                int j = (occupancies[i] * magic) >> (64 - n);
                if (used[j] == 0)
                {
                    used[j] = attacks[i];
                }
                else if (used[j] != attacks[i])
                {
                    break;
                }
            }
            if (i == m)
            {
                return magic;
            }
        }

        // If we reach here, we failed to find a magic number
        throw std::runtime_error("Failed to find magic number");
    }

    Bitboard MagicMoves::generate_occupancy(int index, Bitboard mask) const
    {
        Bitboard occupancy = 0ULL;
        int bits = BitboardUtils::pop_count(mask);
        for (int i = 0; i < bits; i++)
        {
            int square = BitboardUtils::bitscan_forward(mask);
            mask = BitboardUtils::clear_bit(mask, static_cast<Square>(square));

            if (index & (1 << i))
            {
                occupancy |= (1ULL << square);
            }
        }
        return occupancy;
    }

    Bitboard MagicMoves::get_rook_moves(Square sq, Bitboard occupancy) const
    {
        occupancy &= rook_table[sq].mask;
        occupancy *= rook_table[sq].magic;
        occupancy >>= rook_table[sq].shift;
        return rook_table[sq].moves[occupancy];
    }

    Bitboard MagicMoves::get_bishop_moves(Square sq, Bitboard occupancy) const
    {
        occupancy &= bishop_table[sq].mask;
        occupancy *= bishop_table[sq].magic;
        occupancy >>= bishop_table[sq].shift;
        return bishop_table[sq].moves[occupancy];
    }

} // namespace ChessEngine