#include "Instruction.h"
#include <iostream>
void InstructionNext::excecute(ProgramState & state) {
    state.pointer()++;
}

void InstructionPrev::excecute(ProgramState & state) {
    state.pointer()--;
}

void InstructionIncrement::excecute(ProgramState & state) {
    state.setCurrent(state.current() + 1);
}

void InstructionDecrement::excecute(ProgramState & state) {
    state.setCurrent(state.current() - 1);
}

void InstructionPrint::excecute(ProgramState & state) {
    std::cout << (char)state.current();
}

void InstructionCycle::excecute(ProgramState & state) {
    while (state.current()) {
        for (Instruction *instr: this->instructions) {
            instr->excecute(state);
        }
    }
}

void Program::excecute(ProgramState & state) {
    for (Instruction* instr: this->instructions) {
        instr->excecute(state);
    }
}

void CompositeInstruction::appendInstruction(Instruction *instr) {
    this->instructions.push_back(instr);
}
