#ifndef ZOBRIST_H
#define ZOBRIST_H

#include <array>
#include <random>
#include "../core/types.h"

namespace ChessEngine
{

    class Zobrist
    {
    public:
        Zobrist();

        uint64_t get_piece_hash(Piece piece, Color color, Square square) const;
        uint64_t get_castling_hash(CastlingRights rights) const;
        uint64_t get_en_passant_hash(File file) const;
        uint64_t get_side_to_move_hash() const;

    private:
        static constexpr int NUM_PIECES = 6;
        static constexpr int NUM_COLORS = 2;
        static constexpr int NUM_SQUARES = 64;

        std::array<std::array<std::array<uint64_t, NUM_SQUARES>, NUM_COLORS>, NUM_PIECES> piece_keys;
        std::array<uint64_t, 16> castling_keys;  // 4 bits, 2^4 = 16 possibilities
        std::array<uint64_t, 8> en_passant_keys; // One for each file
        uint64_t side_to_move_key;

        void initialize_random_keys();
    };

} // namespace ChessEngine

#endif // ZOBRIST_H