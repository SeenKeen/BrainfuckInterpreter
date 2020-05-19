#include "Executable.h"
#include <stack>
#include <vector>
#include <string>

class Compiler {
    // call stack of brainfuck cycles
    std::stack<CompositeInstruction*> scopes;

    Instruction *make_instruction(char symbol) {
        Instruction * result = nullptr;
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
                scopes.push(new InstructionCycle());
                result = scopes.top();
                break;
            case ']':
                scopes.pop();
                break;
        }
        return result;
    }

public:
    Executable compile(std::string & code) {
        Executable brainfuck_exe;
    }
};

