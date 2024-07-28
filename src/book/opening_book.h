#ifndef OPENING_BOOK_H
#define OPENING_BOOK_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../core/types.h"
#include "../core/move.h"

namespace ChessEngine
{

    class OpeningBook
    {
    public:
        OpeningBook();
        ~OpeningBook();

        bool load(const std::string &filename);
        Move get_book_move(const std::string &fen) const;
        void add_position(const std::string &fen, const Move &move, int weight = 1);
        void save(const std::string &filename) const;

        // Learning functionality
        void update_move_weight(const std::string &fen, const Move &move, int new_weight);

    private:
        struct BookEntry
        {
            Move move;
            int weight;
        };

        std::unordered_map<std::string, std::vector<BookEntry>> book;

        // Helper methods
        Move select_move(const std::vector<BookEntry> &entries) const;
    };

} // namespace ChessEngine

#endif // OPENING_BOOK_H