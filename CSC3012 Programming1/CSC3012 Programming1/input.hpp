//
//  input.hpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 17/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef input_hpp
#define input_hpp

#include <iostream>
#include <string>

#include "AVL.hpp"
#include "Heap.hpp"


class Instructions {
    FILE* file;
public:

    Instructions(std::string filename) {
        file = fopen(filename.c_str(), "r");
        if (file == nullptr) {
            std::cerr << "Failed to read input file \"" << filename << "\"\n";
        }
    }

    ~Instructions() { fclose(file); }

    void executeForAVL() {
        if (file == nullptr) {
            std::cerr << "No instructions\n";
            return;
        }

        AVL<int> *tree = nullptr;

        while (!feof(file)) {
            char instructionBuffer[32];
            fgets(instructionBuffer, 32, file);

            char instruction[3];
            strncpy(instruction, instructionBuffer, 2);

            int integer;
            try {
                integer = std::stoi(std::string(instructionBuffer + 3));
            } catch(std::invalid_argument error) {
                integer = 0;
            }

            executeAVL(instruction, integer, tree);
        }

    }

private:
    void executeHeap(char* instruction, int parameter) {
        
    }

    void executeAVL(char* instruction, int parameter, AVL<int> *&tree) {
        if (strcmp(instruction, "MI") == 0) { std::cout << "MI() -> " << tree->min()->getKey() << "\n"; }
        if (strcmp(instruction, "MA") == 0) { std::cout << "MA() -> " << tree->max()->getKey() << "\n"; }
        if (strcmp(instruction, "IN") == 0) { std::cout << "IN(" << parameter << ")\n"; AVL<int>::insert(tree, parameter); }
        if (strcmp(instruction, "SC") == 0) { std::cout << "SC(" << parameter << ") -> " << tree->successor(parameter)->getKey() << "\n"; }
        if (strcmp(instruction, "SE") == 0) { std::cout << "SE(" << parameter << ") -> " << tree->select(parameter)->getKey() << "\n"; }
        if (strcmp(instruction, "SR") == 0) { std::cout << "SR(" << parameter << ") -> " << tree->search(parameter) << "\n"; }
        if (strcmp(instruction, "RA") == 0) { std::cout << "RA(" << parameter << ") -> " << tree->rank(parameter) << "\n"; }
        if (strcmp(instruction, "PR") == 0) { std::cout << "PR(" << parameter << ") ->\n"; }
        if (strcmp(instruction, "TR") == 0) { std::cout << "TR() ->" << tree->inorder() <<"\n"; }
    }
};


#endif /* input_hpp */
