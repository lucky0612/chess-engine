#include "opening_book.h"
#include <fstream>
#include <random>
#include <sstream>
#include "../utils/string_utils.h"

namespace ChessEngine
{

    OpeningBook::OpeningBook() {}

    OpeningBook::~OpeningBook() {}

    bool OpeningBook::load(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            return false;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::vector<std::string> parts = StringUtils::split(line, '|');
            if (parts.size() != 3)
                continue;

            std::string fen = parts[0];
            Move move = StringUtils::string_to_move(parts[1]);
            int weight = std::stoi(parts[2]);

            add_position(fen, move, weight);
        }

        file.close();
        return true;
    }

    Move OpeningBook::get_book_move(const std::string &fen) const
    {
        auto it = book.find(fen);
        if (it == book.end())
        {
            return Move(); // Return invalid move if position not found
        }
        return select_move(it->second);
    }

    void OpeningBook::add_position(const std::string &fen, const Move &move, int weight)
    {
        book[fen].push_back({move, weight});
    }

    void OpeningBook::save(const std::string &filename) const
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            return;
        }

        for (const auto &entry : book)
        {
            for (const auto &move_entry : entry.second)
            {
                file << entry.first << "|"
                     << StringUtils::move_to_string(move_entry.move) << "|"
                     << move_entry.weight << "\n";
            }
        }

        file.close();
    }

    void OpeningBook::update_move_weight(const std::string &fen, const Move &move, int new_weight)
    {
        auto it = book.find(fen);
        if (it != book.end())
        {
            for (auto &entry : it->second)
            {
                if (entry.move == move)
                {
                    entry.weight = new_weight;
                    return;
                }
            }
        }
        // If move not found, add it
        add_position(fen, move, new_weight);
    }

    Move OpeningBook::select_move(const std::vector<BookEntry> &entries) const
    {
        int total_weight = 0;
        for (const auto &entry : entries)
        {
            total_weight += entry.weight;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, total_weight);
        int random_weight = dis(gen);

        int cumulative_weight = 0;
        for (const auto &entry : entries)
        {
            cumulative_weight += entry.weight;
            if (random_weight <= cumulative_weight)
            {
                return entry.move;
            }
        }

        // This should never happen, but return the last move if it does
        return entries.back().move;
    }

} // namespace ChessEngine