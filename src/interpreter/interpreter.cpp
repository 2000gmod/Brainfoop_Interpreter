#include "interpreter.hpp"

BrainfuckInterpreter::BrainfuckInterpreter(std::string src){
    pointerLoc = 0;
    sourceCode = src;
    if(! syntaxCheck()) throw SyntaxException();
    memorySize = MEMSIZE;
    memory = new cell[memorySize];
    cleanMemory(memorySize);
}
 
BrainfuckInterpreter::BrainfuckInterpreter(std::string src, int _memorySize, bool _debug, int _debugDelay){
    pointerLoc = 0;
    sourceCode = src;
    memorySize = _memorySize;
    memory = new cell[memorySize];
    cleanMemory(memorySize);
    debug = _debug;
    debugDelay = _debugDelay;
}

BrainfuckInterpreter::~BrainfuckInterpreter(){
    delete memory;
}

void BrainfuckInterpreter::run(){
    std::string outBuffer;
    char c = sourceCode[0];
    int64_t counter = -1;
    while (c){
        counter++;
        c = sourceCode[counter];

        if (debug){
            if (std::string("+-><.,[]").find(c) != std::string::npos){
                printDebug(c, 0, memorySize);
                usleep(debugDelay);
            }
        }

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
                if (debug){
                    outBuffer += memory[pointerLoc];
                }
                else printf("%c", memory[pointerLoc]);
                break;

            case ',':
                if (debug){
                    printf(" :: STDIN: ");
                    std::cin >> memory[pointerLoc];
                    printf("\n");
                }
                else{
                    printf("\nIN: ");
                    std::cin >> memory[pointerLoc];
                }
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
    if (debug) printf(" :: OUTPUT >> %s", outBuffer.c_str());
}

void BrainfuckInterpreter::printMemory(int cells){
    printf("\n :: MEMORY DUMP ::\n ::|");
    for(int k = 0; k < cells; k++){
        printf(" %d |", memory[k]);
    }
    printf("::\n :: END ::\n");
}

void BrainfuckInterpreter::printDebug(char c, int start, int last){
    static int step = 0;
    (last > 20) ? last = 20 : last;
    printf(" :: Next instruction: '%c' | Current pointer: 0x%02x | Step N°: %d :: \n", c, pointerLoc, step);
    for(int k = start; k < last; k++){
        printf(" %3d |", memory[k]);
    }
    printf("\n");
    for(int k = start; k < last; k++){
        if(pointerLoc != k) printf("      ");
        else{
            printf("   ^  ");
            break;
        }
    }
    printf("\n\n");
    step += 1;
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