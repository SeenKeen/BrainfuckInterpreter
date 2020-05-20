#include "Instruction.h"

class Interpreter {
    ProgramState state;
    
public:
    void run(Program & exec) {
        exec.excecute(state);
    }
};
