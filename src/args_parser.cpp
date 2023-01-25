#include "args_parser.h"


std::unordered_map<std::string, std::vector<std::string>> ParseArgs(size_t argc, char **argv) {
    std::unordered_map<std::string, std::vector<std::string>> args;
    std::string current_flag;
    for (size_t i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            current_flag = argv[i];
            args[current_flag] = {};
        } else {
            args[current_flag].push_back(argv[i]);
            current_flag.clear();
        }
    }
    return args;
}
