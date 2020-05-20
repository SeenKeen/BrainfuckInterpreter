#pragma once
#include <vector>
#include "ProgramState.h"

class Instruction {
public:
    virtual void excecute(ProgramState & memory)=0;
    virtual bool composite() { return false;}
    virtual ~Instruction()=default;
};

class InstructionNext : public Instruction {

public:
    void excecute(ProgramState & memory) override;
};

class InstructionPrev : public Instruction {

public:
    void excecute(ProgramState & memory) override;
};

class InstructionIncrement : public Instruction {

public:
    void excecute(ProgramState & memory) override;
};

class InstructionDecrement : public Instruction {

public:
    void excecute(ProgramState & memory) override;
};

class InstructionPrint : public Instruction {
    void excecute(ProgramState & memory) override;
};

class CompositeInstruction : public Instruction {
protected:
    std::vector<Instruction*> instructions;
public:
    void excecute(ProgramState & memory) override=0;
    void appendInstruction(Instruction * instr);
    auto begin()                            { return instructions.begin(); }
    auto end()                              { return instructions.end();   }
    std::vector<Instruction*>& children()   { return instructions;         }
    bool composite() override               { return true;                 }

    ~CompositeInstruction() override {
        for (Instruction* instr : instructions) {
            delete instr;
        }
    }
};

class Program : public CompositeInstruction {
public:
    void excecute(ProgramState & memory) override;
};


class InstructionCycle : public CompositeInstruction {
public:
    void excecute(ProgramState & memory) override;
};
