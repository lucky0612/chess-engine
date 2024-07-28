#ifndef UCI_H
#define UCI_H

#include <string>
#include <vector>
#include "../core/types.h"
#include "../core/board.h"
#include "../engine/search.h"
#include "uci_options.h"

namespace ChessEngine
{

    class UCI
    {
    public:
        UCI(Search &search);
        void run();

    private:
        Search &search;
        Board current_board;
        UCIOptions options;

        void process_command(const std::string &command);
        void cmd_uci();
        void cmd_isready();
        void cmd_setoption(const std::vector<std::string> &tokens);
        void cmd_ucinewgame();
        void cmd_position(const std::vector<std::string> &tokens);
        void cmd_go(const std::vector<std::string> &tokens);
        void cmd_stop();
        void cmd_quit();

        void send_best_move(const Move &move);
        void send_info(const SearchInfo &info);
    };

} // namespace ChessEngine

#endif // UCI_H