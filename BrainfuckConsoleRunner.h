#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <unordered_map>
#include "Compiler.h"
#include "Interpreter.h"
#include "UserCommand.h"


class BrainfuckConsoleRunner {


public:
    void run() {
        std::cin.sync_with_stdio(false);
        std::cout << "  Brainfuck console interpreter" << std::endl;
        std::cout << "  Input sevral lines of brainfuck instructions and then blank line\n"
                     "  or:" << std::endl;
        std::cout << "  Type \"file\" and then path     to load code" << std::endl;
        std::cout << "  Type \"exit\"                   to quit" << std::endl;

        auto command = std::unique_ptr<UserCommand>(UserCommandFactory::GetCommand());
        while (!command->onExit()) {
            try {
                command->execute();
            }
            catch (std::exception& e){
                std::cout << "Runtime error : ";
                std::cout << e.what();
            }
            std::cout << std::endl;
            command = std::unique_ptr<UserCommand>(UserCommandFactory::GetCommand());
        }
    }
    void close() {
        std::cout << "Brainfuck interpreter exited\n";
    }
};

