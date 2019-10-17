//
//  input.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 17/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "input.hpp"

Instructions::Instructions(std::string filename) {
    file = fopen(filename.c_str(), "r");
    if (file == nullptr) {
        std::cerr << "Failed to read input file \"" << filename << "\"\n";
    }
}

Instructions::~Instructions() { fclose(file); }

void Instructions::executeForAVL() {
    if (file == nullptr) {
        std::cerr << "No instructions\n";
        return;
    }
    AVL<int>* tree = nullptr;
    char instruction[3];
    int integer;

    while (!feof(file)) {
        getNextInstruction(instruction, integer);
        executeAVL(instruction, integer, tree);
    }
}

void Instructions::executeForHeap() {
    if (file == nullptr) {
        std::cerr << "No instructions\n";
        return;
    }

    Heap<int> heap;
    char instruction[3];
    int integer;

    while (!feof(file)) {
        getNextInstruction(instruction, integer);
        executeHeap(instruction, integer, heap);
    }
}

void Instructions::getNextInstruction(char instruction[], int &integer) {
    char instructionBuffer[32];
    fgets(instructionBuffer, 32, file);

    strncpy(instruction, instructionBuffer, 2);

    try {
        integer = std::stoi(std::string(instructionBuffer + 3));
    } catch(std::invalid_argument error) {
        integer = 0;
    }
}

void Instructions::executeHeap(char* instruction, int parameter, Heap<int> &heap) {
    if (strcmp(instruction, "IN") == 0) { std::cout << "IN(" << parameter << ")\n"; heap.insert(parameter); }
    if (strcmp(instruction, "EX") == 0) { std::cout << "EX() -> " << heap.extractMin() << "\n"; }
}

void Instructions::executeAVL(char* instruction, int parameter, AVL<int> *&tree) {
       if (strcmp(instruction, "MI") == 0) { std::cout << "MI() -> " << tree->min()->getKey() << "\n"; }
       if (strcmp(instruction, "MA") == 0) { std::cout << "MA() -> " << tree->max()->getKey() << "\n"; }
       if (strcmp(instruction, "IN") == 0) { std::cout << "IN(" << parameter << ")\n"; AVL<int>::insert(tree, parameter); }
       if (strcmp(instruction, "SC") == 0) { std::cout << "SC(" << parameter << ") -> " << (tree->successor(parameter) ? tree->successor(parameter)->getKey() : 0) << "\n"; }
       if (strcmp(instruction, "SE") == 0) { std::cout << "SE(" << parameter << ") -> " << tree->select(parameter)->getKey() << "\n"; }
       if (strcmp(instruction, "SR") == 0) { std::cout << "SR(" << parameter << ") -> " << tree->search(parameter) << "\n"; }
       if (strcmp(instruction, "RA") == 0) { std::cout << "RA(" << parameter << ") -> " << tree->rank(parameter) << "\n"; }
       if (strcmp(instruction, "PR") == 0) { std::cout << "PR(" << parameter << ") ->\n"; }
       if (strcmp(instruction, "TR") == 0) { std::cout << "TR() ->" << tree->inorder() <<"\n"; }
   }
