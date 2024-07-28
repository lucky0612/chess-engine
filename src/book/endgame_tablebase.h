#ifndef ENDGAME_TABLEBASE_H
#define ENDGAME_TABLEBASE_H

#include <string>
#include <unordered_map>
#include "../core/types.h"
#include "../core/board.h"

namespace ChessEngine
{

    enum class TablebaseResult
    {
        WIN,
        LOSS,
        DRAW,
        UNKNOWN
    };

    class EndgameTablebase
    {
    public:
        EndgameTablebase();
        ~EndgameTablebase();

        bool load(const std::string &directory);
        TablebaseResult probe(const Board &board) const;

        // On-the-fly tablebase generation
        void generate_tablebase(const std::string &material_configuration);

    private:
        std::unordered_map<std::string, TablebaseResult> tablebase;

        // Helper methods
        std::string get_tablebase_key(const Board &board) const;
        void store_position(const std::string &key, TablebaseResult result);

        // On-the-fly generation helpers
        void generate_positions(Board &board, int depth);
        TablebaseResult evaluate_leaf_node(const Board &board) const;
    };

} // namespace ChessEngine

#endif // ENDGAME_TABLEBASE_H