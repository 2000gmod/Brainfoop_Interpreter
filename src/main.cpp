#include <stdio.h>
#include <fstream>
#include <iostream>

#include "interpreter/interpreter.hpp"

int main(int argc, char* argv[]){
    if (argc == 1){
        std::cout << "No file provided.\n";
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
    
    BrainfuckInterpreter interpreter(code, 30);
    interpreter.run();

    return 0;
}