#include "UserCommand.h"

const std::unordered_map<std::string, std::function<UserCommand*(std::string)>> UserCommandFactory::dispatch =
        {
                {""         , InterpretCommand::construct   },
                {"file"     , FileCommand::construct        },
                {"exit"     , ExitCommand::construct        }
        };

std::string FileCommand::fromFile(std::string& file) {
    FILE * test_open = fopen(file.c_str(), "r");
    if (test_open == nullptr) {
        throw std::runtime_error("no such file or directory");
    } else {
        fclose(test_open);
    }
    std::ifstream source;
    source.open(file);
    std::string brainfuck_code;
    source >> brainfuck_code;
    while (!source.eof()) {
        std::string buffer;
        source >> buffer;
        brainfuck_code += buffer;
    }
    source.close();
    return brainfuck_code;
}
