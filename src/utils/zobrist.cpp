#include "zobrist.h"

namespace ChessEngine
{

    Zobrist::Zobrist()
    {
        initialize_random_keys();
    }

    void Zobrist::initialize_random_keys()
    {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint64_t> dis;

        for (int piece = 0; piece < NUM_PIECES; ++piece)
        {
            for (int color = 0; color < NUM_COLORS; ++color)
            {
                for (int square = 0; square < NUM_SQUARES; ++square)
                {
                    piece_keys[piece][color][square] = dis(gen);
                }
            }
        }

        for (int i = 0; i < 16; ++i)
        {
            castling_keys[i] = dis(gen);
        }

        for (int i = 0; i < 8; ++i)
        {
            en_passant_keys[i] = dis(gen);
        }

        side_to_move_key = dis(gen);
    }

    uint64_t Zobrist::get_piece_hash(Piece piece, Color color, Square square) const
    {
        return piece_keys[static_cast<int>(piece)][static_cast<int>(color)][static_cast<int>(square)];
    }

    uint64_t Zobrist::get_castling_hash(CastlingRights rights) const
    {
        return castling_keys[static_cast<int>(rights)];
    }

    uint64_t Zobrist::get_en_passant_hash(File file) const
    {
        return en_passant_keys[static_cast<int>(file)];
    }

    uint64_t Zobrist::get_side_to_move_hash() const
    {
        return side_to_move_key;
    }

} // namespace ChessEngine