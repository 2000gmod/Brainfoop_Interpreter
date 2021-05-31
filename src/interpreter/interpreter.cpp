#include "interpreter.hpp"

BrainfuckInterpreter::BrainfuckInterpreter(std::string src){
    pointerLoc = 0;
    sourceCode = src;
    if(! syntaxCheck()) throw SyntaxException();
    memorySize = MEMSIZE;
    memory = new byte[memorySize];
    cleanMemory(memorySize);
}

BrainfuckInterpreter::BrainfuckInterpreter(std::string src, int _memorySize){
    pointerLoc = 0;
    sourceCode = src;
    memorySize = _memorySize;
    memory = new byte[memorySize];
    cleanMemory(memorySize);
}

BrainfuckInterpreter::~BrainfuckInterpreter(){
    delete memory;
}

void BrainfuckInterpreter::run(){
    char c = sourceCode[0];
    int64_t counter = -1;
    while (c){
        counter++;
        c = sourceCode[counter];
        switch(c){
            case '>':
                pointerLoc++;
                if (pointerLoc > memorySize){
                    printf("Memory error: pointer is %d", pointerLoc);
                    return;
                }
                break;

            case '<':
                pointerLoc--;
                if (pointerLoc < 0){
                    printf("Memory error: pointer is %d", pointerLoc);
                    return;
                }
                break;

            case '+':
                memory[pointerLoc] += 1;
                break;

            case '-':
                memory[pointerLoc] -= 1;
                break;

            case '.':
                printf("%c", memory[pointerLoc]);
                break;

            case ',':
                std::cin >> memory[pointerLoc];
                break;
            
            case '[':
                if(memory[pointerLoc] == 0){
                    int bracketLevel = 1;
                    do {
                        counter++;
                        c = sourceCode[counter];
                        if(c == '[') bracketLevel++;
                        else if (c == ']') bracketLevel--;
                    } while(bracketLevel != 0);
                }
                else {
                    if (isInStack(counter) == false) bracketStack.push_back(counter);
                }
                break;
            
            case ']':
                if(memory[pointerLoc] != 0){
                    counter = bracketStack.back();
                }
                else {
                    if(bracketStack.size() > 0) bracketStack.pop_back();
                }
                break;
        }
    }
}

void BrainfuckInterpreter::printMemory(int cells){
    printf("\n :: MEMORY DUMP ::\n ::|");
    for(int k = 0; k < cells; k++){
        printf(" %d |", memory[k]);
    }
    printf("::\n :: END ::\n");
}


bool BrainfuckInterpreter::isInStack(int64_t in){
    for (int64_t k : bracketStack){
        if (in == k) return true;
    }
    return false;
}

void BrainfuckInterpreter::cleanMemory(int size){
    for(int k = 0; k < size; k++){
        memory[k] = 0;
    }
}

bool BrainfuckInterpreter::syntaxCheck(){
    int bracketCount = 0;
    for(char c : sourceCode){
        if (c == '[') bracketCount++;
        if (c == ']') bracketCount--;
    }
    return (bracketCount == 0);
}