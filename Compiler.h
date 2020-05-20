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
    // class for excecuting some action after its destruction
    // MAIN OBJECTIVE : delay execution of certain actions till going out of scope

    std::function<void()> action;

public:
    PostExecuter(std::function<void()> action = [] () {}) :
    action(std::move(action)) {};

    ~PostExecuter() { action(); };
};


class Compiler {
    // call stack of brainfuck cycles
    std::vector<CompositeInstruction*> scopes;

    std::pair<Instruction*, PostExecuter> make_instruction(char symbol) {
        // factory method (only for internal use)
        Instruction * result = nullptr;
        std::function<void()> stack_pusher = [] () {};
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
                stack_pusher = [&, result] () {
                    scopes.push_back((CompositeInstruction*)result);
                };
                break;
            case ']':
                scopes.pop_back();
                break;
            case '.':
                result = new InstructionPrint();
                break;
            default:
                throw std::runtime_error("invalid command");
        }
        return std::make_pair(result, stack_pusher);
    }
    bool check_code(std::string & code) {
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
    Program * compile(std::string & code) {
        if (!check_code(code)) {
            throw std::runtime_error("invalid cycles nesting");
        }
        Program * root = new Program;
        scopes = std::vector<CompositeInstruction*> { root };
        for (char symbol : code) {
            if (symbol == '\n' || symbol == ' ') {
                continue;
            }
            auto compiled = make_instruction(symbol);
            Instruction * compiled_instruction = compiled.first;
            // if instruction is to be added to tree
            if (compiled_instruction) {
                scopes.back()->appendInstruction(compiled_instruction);
            }
            // PostExcecuter may perform additional actions to maintain stack
        }
        return root;
    }
};

