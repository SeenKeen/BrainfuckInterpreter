#include <vector>
#include "ProgramState.cpp"

class Instruction {
public:
    virtual void excecute(ProgramState & memory)=0;
    virtual bool composite() { return false;}
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

class CompositeInstruction : public Instruction {
protected:
    std::vector<Instruction*> instructions;
public:
    void excecute(ProgramState & memory) override=0;
    void appendInstruction(Instruction * instr);
    std::vector<Instruction*>& children() { return instructions; };
    bool composite() override { return true;}
};

class Program : public CompositeInstruction {

    void excecute(ProgramState & memory) override;
};


class InstructionCycle : public CompositeInstruction {

    void excecute(ProgramState & memory) override;
};
