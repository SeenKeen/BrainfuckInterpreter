#pragma once
#include "Instruction.h"
#include <stack>
#include <utility>
#include <vector>
#include <string>
#include <functional>
#include <utility>
#include <stdexcept>
#include <exception>


class PostExecuter {
    // class for delaying excecution of some action
    std::function<void()> action;

public:
    PostExecuter(std::function<void()> action = [] () {}) :
    action(std::move(action)) {};

    void performAction() {
        action();
    }
    ~PostExecuter()=default;
};


class Compiler {
    // call stack of brainfuck cycles
    std::vector<CompositeInstruction*> scopes;

    std::pair<Instruction*, PostExecuter> make_instruction(char symbol) {
        // factory method (only for internal use)
        Instruction * result = nullptr;
        std::function<void()> stack_handler = [] () {};
        switch (symbol) {
            case '>':
                result = new InstructionNext();
                break;
            case '<':
                result = new InstructionPrev();
                break;
            case '+':
                result = new InstructionIncrement();
                break;
            case '-':
                result = new InstructionDecrement();
                break;
            case '[':
                result = new InstructionCycle();
                // after adding to instruction tree this instruction will be added to "call stack"
                stack_handler = [&, result] () {
                    scopes.push_back((CompositeInstruction*)result);
                };
                break;
            case ']':
                // this isntruction must pop current scope from stack
                stack_handler = [&, result] () {
                    scopes.pop_back();
                };
                break;
            case '.':
                result = new InstructionPrint();
                break;
            case ' ':
                break;
            case '\n':
                break;
            case '\t':
                break;
            default:
                throw std::runtime_error("invalid command");
        }
        return std::make_pair(result, stack_handler);
    }
    bool check_code(const std::string & code) {
        // checks whether braces structure of brainfuck code is correct
        int balance = 0;
        for (auto symbol : code) {
            switch(symbol) {
                case '[':
                    balance++;
                    break;
                case ']':
                    balance--;
                    break;
            }
            if (balance < 0) {
                return false;
            }
        }
        return balance == 0;
    }

public:
    Program * compile(const std::string & code) {
        if (!check_code(code)) {
            throw std::runtime_error("invalid cycles nesting");
        }
        Program * root = new Program;
        scopes = std::vector<CompositeInstruction*> { root };
        for (char symbol : code) {
            auto compiled = make_instruction(symbol);
            Instruction * compiled_instruction = compiled.first;
            PostExecuter stack_handler = compiled.second;
            // if instruction is to be added to tree
            if (compiled_instruction) {
                try {
                    scopes.back()->appendInstruction(compiled_instruction);
                } catch (std::exception & e) {
                    // in case of exception root will be lost
                    // so tree destruction is needed to prevent memory leak
                    delete root;
                    // rethrow
                    throw e;
                }
            }
            // PostExcecuter may perform additional actions to maintain stack
            stack_handler.performAction();
        }
        return root;
    }
};
















