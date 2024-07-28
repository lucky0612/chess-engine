#ifndef UCI_OPTIONS_H
#define UCI_OPTIONS_H

#include <string>
#include <unordered_map>
#include <vector>

namespace ChessEngine
{

    enum class OptionType
    {
        CHECK,
        SPIN,
        COMBO,
        BUTTON,
        STRING
    };

    struct UCIOption
    {
        OptionType type;
        std::string default_value;
        std::string current_value;
        int min_value;
        int max_value;
        std::vector<std::string> combo_options;
    };

    class UCIOptions
    {
    public:
        UCIOptions();

        void add_option(const std::string &name, const UCIOption &option);
        void set_option(const std::string &name, const std::string &value);
        std::string get_option(const std::string &name) const;
        void print_options() const;

    private:
        std::unordered_map<std::string, UCIOption> options;
    };

} // namespace ChessEngine

#endif // UCI_OPTIONS_H