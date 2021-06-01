#include <stdio.h>
#include <fstream>
#include <iostream>

#include <string.h>

#include "interpreter/interpreter.hpp"

int main(int argc, char* argv[]){
    if (argc == 1 || argc > 4){
        std::cout << "Usage: ./bfpint <file.bf> <-v> <VerboseTime [ms]>\n";
        return 1;
    }

    FILE* file;
    std::string code;
    char c;
    
    file = fopen(argv[1], "r");
    if (file != NULL){
        while ((c = fgetc(file)) != EOF ){
            code += c;
        }
        fclose(file);
    }
    else std::cout << "Unable to open file"; 

    bool debugFlag = false;
    int debugTime = 50000;
    if(argc >= 3){
        if(!strcmp(argv[2], "-v")) debugFlag = true;

        if (argc == 4) debugTime = stoi((std::string)argv[3]) * 1000;
    }
    
    BrainfuckInterpreter interpreter(code, 30, debugFlag, debugTime);
    interpreter.run();

    return 0;
}