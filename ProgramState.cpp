
class ProgramState {
    using size_t = unsigned int;
    static const size_t memory_size = 30000;
    int __memory[memory_size];
    size_t __pointer;
    ProgramState() {
        for (size_t i = 0; i < memory_size; ++i) {
            __memory[i] = 0;
        }
        __pointer = 0;
    }

public:
    int& operator [] (int place) {
        return __memory[place];
    }
    size_t& pointer() {
        return __pointer;
    }
    int& current() {
        return __memory[__pointer];
    }
};
