#include "Instruction.h"
#include <iostream>
void InstructionNext::execute(ProgramState & state) {
    state.pointer()++;
}

void InstructionPrev::execute(ProgramState & state) {
    state.pointer()--;
}

void InstructionIncrement::execute(ProgramState & state) {
    state.setCurrent(state.current() + 1);
}

void InstructionDecrement::execute(ProgramState & state) {
    state.setCurrent(state.current() - 1);
}

void InstructionPrint::execute(ProgramState & state) {
    std::cout << (unsigned char)state.current();
    std::cout.flush();
}

void InstructionCycle::execute(ProgramState & state) {
    while (state.current()) {
        for (Instruction *instr: this->instructions) {
            instr->execute(state);
        }
    }
}

void Program::execute(ProgramState & state) {
    for (Instruction* instr: this->instructions) {
        instr->execute(state);
    }
}

void CompositeInstruction::appendInstruction(Instruction *instr) {
    this->instructions.push_back(instr);
}
