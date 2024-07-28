#include "uci_options.h"
#include <iostream>
#include <algorithm>

namespace ChessEngine
{

    UCIOptions::UCIOptions()
    {
        // Add default options
        add_option("Hash", {OptionType::SPIN, "16", "16", 1, 1024});
        add_option("Threads", {OptionType::SPIN, "1", "1", 1, 128});
        add_option("MultiPV", {OptionType::SPIN, "1", "1", 1, 500});
        add_option("Ponder", {OptionType::CHECK, "false", "false"});
        add_option("OwnBook", {OptionType::CHECK, "false", "false"});
        add_option("UCI_AnalyseMode", {OptionType::CHECK, "false", "false"});
    }

    void UCIOptions::add_option(const std::string &name, const UCIOption &option)
    {
        options[name] = option;
    }

    void UCIOptions::set_option(const std::string &name, const std::string &value)
    {
        if (options.find(name) != options.end())
        {
            UCIOption &option = options[name];

            switch (option.type)
            {
            case OptionType::CHECK:
                if (value == "true" || value == "false")
                {
                    option.current_value = value;
                }
                break;
            case OptionType::SPIN:
            {
                int int_value = std::stoi(value);
                if (int_value >= option.min_value && int_value <= option.max_value)
                {
                    option.current_value = value;
                }
            }
            break;
            case OptionType::COMBO:
                if (std::find(option.combo_options.begin(), option.combo_options.end(), value) != option.combo_options.end())
                {
                    option.current_value = value;
                }
                break;
            case OptionType::BUTTON:
                // Button doesn't store a value
                break;
            case OptionType::STRING:
                option.current_value = value;
                break;
            }
        }
    }

    std::string UCIOptions::get_option(const std::string &name) const
    {
        auto it = options.find(name);
        if (it != options.end())
        {
            return it->second.current_value;
        }
        return "";
    }

    void UCIOptions::print_options() const
    {
        for (const auto &[name, option] : options)
        {
            std::cout << "option name " << name << " type ";
            switch (option.type)
            {
            case OptionType::CHECK:
                std::cout << "check default " << option.default_value;
                break;
            case OptionType::SPIN:
                std::cout << "spin default " << option.default_value
                          << " min " << option.min_value
                          << " max " << option.max_value;
                break;
            case OptionType::COMBO:
                std::cout << "combo default " << option.default_value;
                for (const auto &var : option.combo_options)
                {
                    std::cout << " var " << var;
                }
                break;
            case OptionType::BUTTON:
                std::cout << "button";
                break;
            case OptionType::STRING:
                std::cout << "string default " << option.default_value;
                break;
            }
            std::cout << std::endl;
        }
    }

} // namespace ChessEngine