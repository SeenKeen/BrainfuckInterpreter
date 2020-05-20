cmake_minimum_required(VERSION 3.15)
project(BrainfuckInterpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(BrainfuckInterpreter main.cpp Instruction.cpp Instruction.h Interpreter.cpp Compiler.h ProgramState.h BrainfuckConsoleRunner.h)
