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
        std::string brainfuck_code;
        std::cin >> brainfuck_code;
        return brainfuck_code;
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
        std::cout << "  Type \"file\" and then path     to load code" << std::endl;
        std::cout << "  Type \"exit\"                   to quit" << std::endl;
        std::string brainfuck_code = singleCommand();
        while (brainfuck_code != "exit") {
            try {
                if (brainfuck_code == "file") {
                    std::string filename;
                    std::cin >> filename;
                    brainfuck_code = fromFile(filename);
                }
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
            brainfuck_code = singleCommand();
        }
    }
    void close() {
        std::cout << "Brainfuck interpreter exited\n";
    }
};

