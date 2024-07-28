#include "endgame_tablebase.h"
#include <fstream>
#include <filesystem>
#include "../utils/string_utils.h"

namespace ChessEngine
{

    EndgameTablebase::EndgameTablebase() {}

    EndgameTablebase::~EndgameTablebase() {}

    bool EndgameTablebase::load(const std::string &directory)
    {
        for (const auto &entry : std::filesystem::directory_iterator(directory))
        {
            if (entry.path().extension() == ".etb")
            {
                std::ifstream file(entry.path());
                if (!file.is_open())
                    continue;

                std::string line;
                while (std::getline(file, line))
                {
                    std::vector<std::string> parts = StringUtils::split(line, '|');
                    if (parts.size() != 2)
                        continue;

                    std::string key = parts[0];
                    TablebaseResult result = static_cast<TablebaseResult>(std::stoi(parts[1]));
                    tablebase[key] = result;
                }

                file.close();
            }
        }

        return !tablebase.empty();
    }

    TablebaseResult EndgameTablebase::probe(const Board &board) const
    {
        std::string key = get_tablebase_key(board);
        auto it = tablebase.find(key);
        if (it != tablebase.end())
        {
            return it->second;
        }
        return TablebaseResult::UNKNOWN;
    }

    void EndgameTablebase::generate_tablebase(const std::string &material_configuration)
    {
        // Initialize a board with the given material configuration
        Board board = Board::from_material_config(material_configuration);

        generate_positions(board, 0);

        // Save the generated tablebase
        std::string filename = material_configuration + ".etb";
        std::ofstream file(filename);
        for (const auto &entry : tablebase)
        {
            file << entry.first << "|" << static_cast<int>(entry.second) << "\n";
        }
        file.close();
    }

    std::string EndgameTablebase::get_tablebase_key(const Board &board) const
    {
        // Generate a unique key for the board position
        // This could be a simplified FEN or a custom format
        return board.to_fen();
    }

    void EndgameTablebase::store_position(const std::string &key, TablebaseResult result)
    {
        tablebase[key] = result;
    }

    void EndgameTablebase::generate_positions(Board &board, int depth)
    {
        std::string key = get_tablebase_key(board);

        // If position already evaluated, return
        if (tablebase.find(key) != tablebase.end())
        {
            return;
        }

        // If leaf node, evaluate and store
        if (depth == 0 || board.is_game_over())
        {
            TablebaseResult result = evaluate_leaf_node(board);
            store_position(key, result);
            return;
        }

        // Generate all legal moves
        std::vector<Move> moves = board.generate_legal_moves();

        // Recursive call for each move
        for (const Move &move : moves)
        {
            board.make_move(move);
            generate_positions(board, depth - 1);
            board.undo_move(move);
        }

        // Evaluate current position based on child positions
        // This is a simplified evaluation, you might want to implement a more sophisticated one
        TablebaseResult best_result = board.side_to_move() == Color::WHITE ? TablebaseResult::LOSS : TablebaseResult::WIN;
        for (const Move &move : moves)
        {
            board.make_move(move);
            TablebaseResult child_result = probe(board);
            board.undo_move(move);

            if (board.side_to_move() == Color::WHITE)
            {
                if (child_result == TablebaseResult::WIN)
                {
                    best_result = TablebaseResult::WIN;
                    break;
                }
                else if (child_result == TablebaseResult::DRAW)
                {
                    best_result = TablebaseResult::DRAW;
                }
            }
            else
            {
                if (child_result == TablebaseResult::LOSS)
                {
                    best_result = TablebaseResult::LOSS;
                    break;
                }
                else if (child_result == TablebaseResult::DRAW)
                {
                    best_result = TablebaseResult::DRAW;
                }
            }
        }

        store_position(key, best_result);
    }

    TablebaseResult EndgameTablebase::evaluate_leaf_node(const Board &board) const
    {
        if (board.is_checkmate())
        {
            return board.side_to_move() == Color::WHITE ? TablebaseResult::LOSS : TablebaseResult::WIN;
        }
        else if (board.is_stalemate() || board.is_draw_by_repetition() || board.is_draw_by_fifty_move_rule())
        {
            return TablebaseResult::DRAW;
        }
        // Implement other evaluation logic here
        return TablebaseResult::UNKNOWN;
    }

} // namespace ChessEngine