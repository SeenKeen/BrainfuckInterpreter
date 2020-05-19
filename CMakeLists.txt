cmake_minimum_required(VERSION 3.15)
project(BrainfuckInterpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(BrainfuckInterpreter main.cpp Executable.cpp Executable.h Instruction.cpp Instruction.h ProgramState.cpp Interpreter.cpp Compiler.cpp Compiler.h)
