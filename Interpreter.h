#pragma once
#include "Instruction.h"

class Interpreter {
    ProgramState state;
    
public:
    void run(Program & exec) {
        exec.execute(state);
    }
};
