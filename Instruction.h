#pragma once
#include <vector>
#include "ProgramState.h"

class Instruction {
    // an execution unit and arbitrary node of syntax tree
public:
    Instruction()=default;
    virtual void execute(ProgramState & memory)=0;
    virtual bool composite() { return false;} // returns if the node is a branch
    virtual ~Instruction()=default;
};

class InstructionNext : public Instruction {

public:
    void execute(ProgramState & memory) override;
};

class InstructionPrev : public Instruction {

public:
    void execute(ProgramState & memory) override;
};

class InstructionIncrement : public Instruction {

public:
    void execute(ProgramState & memory) override;
};

class InstructionDecrement : public Instruction {

public:
    void execute(ProgramState & memory) override;
};

class InstructionPrint : public Instruction {
    void execute(ProgramState & memory) override;
};

class CompositeInstruction : public Instruction {
    // Composite instruction serves as a branch in brainfuck exe syntax tree
protected:
    std::vector<Instruction*> instructions;
public:
    CompositeInstruction()=default;
    void execute(ProgramState & memory) override=0;
    void appendInstruction(Instruction * instr);
    std::vector<Instruction*>& children()   { return instructions;         }
    bool composite() override               { return true;                 }

    ~CompositeInstruction() override {
        for (Instruction* instr : instructions) {
            delete instr;
        }
    }
};

class Program : public CompositeInstruction {
    // intended to be the root of any brainfuck exe
public:
    void execute(ProgramState & memory) override;
};


class InstructionCycle : public CompositeInstruction {
public:
    void execute(ProgramState & memory) override;
};
