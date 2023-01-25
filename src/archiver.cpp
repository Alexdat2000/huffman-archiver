#include "args_parser.h"
#include "decode.h"
#include "encode.h"
#include "iobuffer.h"
#include <fstream>

const std::string HELP_MESSAGE = "archiver -c archive_name file1 [file2 ...] -- archive files file1, file2, ... and save the result to file archive_name\n"
                                 "archiver -d archive_name -- unarchive the files from archive_name and put them into the current directory\n"
                                 "archiver -h -- print help on using the program";

int main(int argc, char **argv) {
    try {
        auto args = ParseArgs(argc, argv);
        if (args.count("-h")) {
            std::cout << HELP_MESSAGE << std::endl;
            return 0;
        }
        if (args.count("-c")) {
            if (args["-c"].empty() || args[""].empty()) {
                std::cout << HELP_MESSAGE << std::endl;
                return 111;
            }
            ofstream out(args["-c"][0] + ".txt");


        }
    } catch (const DecoderError&) {
        std::cerr << "Error while decoding archive" << std::endl;
        return 111;
    } catch (const DecoderError&) {
        std::cerr << "Error while reading archive" << std::endl;
        return 111;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 111;
    }
    return 0;
}
