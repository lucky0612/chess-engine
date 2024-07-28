#include "uci.h"
#include <iostream>
#include <sstream>
#include "../utils/string_utils.h"

namespace ChessEngine
{

    UCI::UCI(Search &search) : search(search), current_board(Board::start_position()) {}

    void UCI::run()
    {
        std::string line;
        while (std::getline(std::cin, line))
        {
            process_command(line);
        }
    }

    void UCI::process_command(const std::string &command)
    {
        std::vector<std::string> tokens = StringUtils::split(command, ' ');
        if (tokens.empty())
            return;

        std::string cmd = tokens[0];
        if (cmd == "uci")
            cmd_uci();
        else if (cmd == "isready")
            cmd_isready();
        else if (cmd == "setoption")
            cmd_setoption(tokens);
        else if (cmd == "ucinewgame")
            cmd_ucinewgame();
        else if (cmd == "position")
            cmd_position(tokens);
        else if (cmd == "go")
            cmd_go(tokens);
        else if (cmd == "stop")
            cmd_stop();
        else if (cmd == "quit")
            cmd_quit();
    }

    void UCI::cmd_uci()
    {
        std::cout << "id name AdvancedMCTS" << std::endl;
        std::cout << "id author Your Name" << std::endl;

        options.print_options();

        std::cout << "uciok" << std::endl;
    }

    void UCI::cmd_isready()
    {
        std::cout << "readyok" << std::endl;
    }

    void UCI::cmd_setoption(const std::vector<std::string> &tokens)
    {
        if (tokens.size() < 5)
            return;
        std::string name = tokens[2];
        std::string value = tokens[4];
        options.set_option(name, value);
        search.update_options(options);
    }

    void UCI::cmd_ucinewgame()
    {
        search.clear();
        current_board = Board::start_position();
    }

    void UCI::cmd_position(const std::vector<std::string> &tokens)
    {
        size_t moves_index = std::find(tokens.begin(), tokens.end(), "moves") - tokens.begin();

        if (tokens[1] == "startpos")
        {
            current_board = Board::start_position();
        }
        else if (tokens[1] == "fen")
        {
            std::string fen;
            for (size_t i = 2; i < moves_index && i < tokens.size(); ++i)
            {
                fen += tokens[i] + " ";
            }
            current_board = Board::from_fen(fen);
        }

        if (moves_index < tokens.size())
        {
            for (size_t i = moves_index + 1; i < tokens.size(); ++i)
            {
                Move move = StringUtils::string_to_move(tokens[i]);
                current_board.make_move(move);
            }
        }
    }

    void UCI::cmd_go(const std::vector<std::string> &tokens)
    {
        int depth = -1;
        int movetime = -1;
        int wtime = -1, btime = -1, winc = 0, binc = 0;
        int movestogo = 0;

        for (size_t i = 1; i < tokens.size(); i += 2)
        {
            if (tokens[i] == "depth")
                depth = std::stoi(tokens[i + 1]);
            else if (tokens[i] == "movetime")
                movetime = std::stoi(tokens[i + 1]);
            else if (tokens[i] == "wtime")
                wtime = std::stoi(tokens[i + 1]);
            else if (tokens[i] == "btime")
                btime = std::stoi(tokens[i + 1]);
            else if (tokens[i] == "winc")
                winc = std::stoi(tokens[i + 1]);
            else if (tokens[i] == "binc")
                binc = std::stoi(tokens[i + 1]);
            else if (tokens[i] == "movestogo")
                movestogo = std::stoi(tokens[i + 1]);
        }

        search.start_search(current_board, depth, movetime, wtime, btime, winc, binc, movestogo);
    }

    void UCI::cmd_stop()
    {
        search.stop();
    }

    void UCI::cmd_quit()
    {
        search.stop();
        exit(0);
    }

    void UCI::send_best_move(const Move &move)
    {
        std::cout << "bestmove " << StringUtils::move_to_string(move) << std::endl;
    }

    void UCI::send_info(const SearchInfo &info)
    {
        std::cout << "info";
        if (info.depth > 0)
            std::cout << " depth " << info.depth;
        if (info.seldepth > 0)
            std::cout << " seldepth " << info.seldepth;
        if (info.time > 0)
            std::cout << " time " << info.time;
        if (info.nodes > 0)
            std::cout << " nodes " << info.nodes;
        if (!info.pv.empty())
        {
            std::cout << " pv";
            for (const auto &move : info.pv)
            {
                std::cout << " " << StringUtils::move_to_string(move);
            }
        }
        if (info.score != -INFINITE)
        {
            std::cout << " score cp " << info.score;
            if (info.mate)
                std::cout << " mate " << info.mate;
        }
        std::cout << std::endl;
    }

} // namespace ChessEngine