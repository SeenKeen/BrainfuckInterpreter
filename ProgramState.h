#pragma once

#include <exception>
#include <string>
#include <stdexcept>

class ProgramState {
    // Class for maintaining state of brainfuck memory
    
    using size_t = unsigned int;
    static const size_t memory_size = 30000;
    int __memory[memory_size];                  
    size_t __pointer;                           // current position

public:
    ProgramState() {
        for (size_t i = 0; i < memory_size; ++i) {
            __memory[i] = 0;
        }
        __pointer = 0;
    }

    int operator [] (int place) const {
        if (__pointer >= memory_size) {
            throw std::range_error("Brainfuck memory read out of bounds");
        }
        return __memory[place];
    }
    int setCurrent(int value) {
        if (__pointer >= memory_size) {
            throw std::range_error("Brainfuck memory write out of bounds");
        }
        __memory[__pointer] = value;
    }
    size_t& pointer() {
        return __pointer;
    }
    int current() const {
        if (__pointer >= memory_size) {
            throw std::range_error("Brainfuck memory read out of bounds");
        }
        return __memory[__pointer];
    }
};
