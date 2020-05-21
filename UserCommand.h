#pragma once
#include <algorithm>
#include <string>
#include <unordered_map>
#include <functional>
#include <utility>
#include <fstream>
#include <memory>
#include <iostream>
#include "Compiler.h"
#include "Interpreter.h"

class UserCommand {

protected:
    static void CompilationInterpretation(const std::string& brainfuck_code) {
        Compiler compiler;
        Interpreter interpreter;
        auto exe = std::unique_ptr<Program>(compiler.compile(brainfuck_code));
        std::cout << "output : ";
        interpreter.run(*exe);
    }

public:

    UserCommand()=default;

    virtual void execute()=0;
    virtual bool onExit() { return false; }

};

class InterpretCommand : public UserCommand {
    std::string code;

public:
    explicit InterpretCommand(const std::string & args) : code(args) {}

    void execute() override {
        UserCommand::CompilationInterpretation(code);
    }
    static UserCommand * construct(const std::string& args) {
        return new InterpretCommand(args);
    };
};

class FileCommand : public UserCommand {
    std::string filepath;

    static std::string fromFile(std::string& file);

public:
    explicit FileCommand(const std::string & args) : filepath(args) {}

    void execute() override {
        UserCommand::CompilationInterpretation(fromFile(filepath));
    }
    static UserCommand * construct(const std::string& args) {
        return new FileCommand(args);
    };
};

class ExitCommand : public UserCommand {

public:
    explicit ExitCommand(const std::string & args) {};

    bool onExit() override { return true; }
    void execute() override {}

    static UserCommand * construct(const std::string& args) {
        return new ExitCommand(args);
    };
};


class UserCommandFactory {
    static const std::unordered_map<std::string, std::function<UserCommand*(std::string)>> dispatch;

    static std::pair<std::string, std::string> parse_input(const std::string& user_input) {
        auto pivot = std::min(user_input.find(' '), user_input.size());
        return std::make_pair(user_input.substr(0, pivot),
                              user_input.substr(pivot, user_input.size()));
    }

public:
    static UserCommand* GetCommand() {
        std::cout << "*&@!))) ";
        std::string user_input;
        std::getline(std::cin, user_input);
        auto parsed = parse_input(user_input);
        std::string command = parsed.first;
        std::string args = parsed.second;
        if (dispatch.find(command) == dispatch.end() || command.empty()) {
            // if any command recognized
            args = command + args;
            command = "";
            std::string buffer;
            std::getline(std::cin, buffer);
            while (buffer.size()) {
                args += buffer;
                std::getline(std::cin, buffer);
            }
        } else {
            auto argstart = std::find_if(args.begin(), args.end(), [] (char symb) {
                return symb != ' ';
            });
            args = std::string(argstart, args.end());
        }
        return dispatch.at(command)(args);
    }
};


