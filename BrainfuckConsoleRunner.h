#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include "Compiler.h"
#include "Interpreter.cpp"

class BrainfuckConsoleRunner {

    std::string singleCommand() {

        std::cout << "*&@!))) ";
        std::string user_input;
        std::getline(std::cin, user_input);
        return user_input;
    }
    std::string fromFile(std::string& file) {
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
public:
    void run() {
        std::cout << "  Brainfuck console interpreter" << std::endl;
        std::cout << "  Input one line of brainfuck instructions or:" << std::endl;
        std::cout << "  Type \"file\" and then path     to load code" << std::endl;
        std::cout << "  Type \"exit\"                   to quit" << std::endl;
        auto extract_first_word = [] (const std::string& line) -> std::string {
            return line.substr(0, line.find(' '));
        };
        std::string user_input = singleCommand();
        while (extract_first_word(user_input) != "exit") {
            try {
                std::string brainfuck_code;
                // 1. command handling
                if (extract_first_word(user_input) == "file") {
                    std::string filename ;
                    brainfuck_code = fromFile(filename);
                } else {
                    brainfuck_code = user_input;
                }
                // 2. Compilation & interpretation
                Compiler compiler;
                Interpreter interpreter;
                auto exe = std::unique_ptr<Program>(compiler.compile(brainfuck_code));
                std::cout << "output : ";
                interpreter.run(*exe);
            }
            catch (std::exception& e){
                std::cout << "Runtime error : ";
                std::cout << e.what();
            }
            std::cout << std::endl;
            user_input = singleCommand();
        }
    }
    void close() {
        std::cout << "Brainfuck interpreter exited\n";
    }
};

