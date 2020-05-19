#include <stack>
#include "Instruction.h"

class Executable {
    Program * program;
    Instruction * current;
    std::stack<CompositeInstruction*> call_stack;
public:
    Executable(Program * prog) : current(prog) {
        while (current->composite()) {
            auto * current_node = (CompositeInstruction*)current;
            call_stack.push(current_node);
            auto & children = current_node->children();
            if (children.size()) {
                current = children[0];
            } else {
                call_stack.pop();
                current = call_stack.top();
            }
        }
    }
    Instruction * next() {

    }
};

