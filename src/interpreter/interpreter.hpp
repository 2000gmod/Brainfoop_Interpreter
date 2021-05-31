#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <vector>
#include <array>
#include <iostream>

#include <exception>

#include <unistd.h>

#define MEMSIZE 30


typedef unsigned char byte;

class BrainfuckInterpreter{
    private:
        std::string sourceCode;
        byte* memory;
        int pointerLoc;
        std::vector<int64_t> bracketStack;
        int memorySize;

        bool isInStack(int64_t in);
        void cleanMemory(int size);
        bool syntaxCheck();
    
    public:
        BrainfuckInterpreter(std::string src);
        BrainfuckInterpreter(std::string src, int memorySize);
        ~BrainfuckInterpreter();
        void run();
        void printMemory(int cells);
};

class SyntaxException : public std::exception{
    public:
    const char * what() const throw(){
        return "Syntax error: brackets are unmatched";
    }
};

#endif