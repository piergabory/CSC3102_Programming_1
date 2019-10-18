//
//  input.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory and Wasim Alam on 17/10/2019.
//
//

#include "Instructions.hpp"

namespace CSC3012_P1 {

static std::string nth(unsigned int count) {
    std::string out = std::to_string(count);
    switch (count % 10) {
        case 1: out += "st "; break;
        case 2: out += "nd "; break;
        case 3: out += "rd "; break;
        default: out += "th "; break;
    }
    return out;
}



Instructions::Instructions(std::string filename):
input(nullptr),
buffer(""),
extract_min_count(0)
{
    input = fopen(filename.c_str(), "r");
    if (input == nullptr) {
        std::cerr << "Failed to read input file \"" << filename << "\"\n";
    }
}



Instructions::~Instructions() { fclose(input); }



void Instructions::executeForAVL() {
    if (input == nullptr) {
        std::cerr << "No instructions\n";
        return;
    }
    AVL<int>* tree = nullptr;
    char instruction[3];
    int integer;
    stopwatch.refreshTimer();

    buffer = "";
    stopwatch.startTimer();
    while (!feof(input)) {
        std::string instruction_string = getNextInstruction(instruction, integer);
        if (strlen(instruction) == 2) {
            buffer += executeAVL(instruction, integer, tree);
            if (strcmp(instruction, "IN") != 0) {
                buffer += "\t//" + instruction_string;
            }
        }
    }
    stopwatch.stopTimer();
    buffer += std::to_string((int) stopwatch.getElapsedTime());
    buffer += " micro-sec\n";
}




void Instructions::executeForHeap() {
    if (input == nullptr) {
        std::cerr << "No instructions\n";
        return;
    }

    Heap<int> heap;
    char instruction[3];
    int integer;
    stopwatch.refreshTimer();

    buffer = "";
    stopwatch.startTimer();
    while (!feof(input)) {
        getNextInstruction(instruction, integer);
        buffer += executeHeap(instruction, integer, heap);
    }
    stopwatch.stopTimer();
    buffer += std::to_string((int) stopwatch.getElapsedTime());
    buffer += " micro-sec\n";
}




void Instructions::saveTo(std::string filename) {
    FILE* output = fopen(filename.c_str(), "w");

    if (output == nullptr) {
        std::cerr << "Failed to create output file.\n";
        return;
    }

    fputs(buffer.c_str(), output);
    fclose(output);

    std::cout << "Results saved in " << filename << "\n";
}




std::string Instructions::getNextInstruction(char instruction[], int &integer) {
    char instructionBuffer[32];
    fgets(instructionBuffer, 32, input);
    strncpy(instruction, instructionBuffer, 2);

    try {
        integer = std::stoi(std::string(instructionBuffer + 3));
    } catch(std::invalid_argument error) {
        integer = 0;
    }

    return std::string(instructionBuffer);
}




std::string Instructions::executeHeap(char* instruction, int parameter, Heap<int> &heap) {
    std::string out = "";
    if (strcmp(instruction, "IN") == 0) { heap.insert(parameter); }
    if (strcmp(instruction, "EX") == 0) {
        int result = heap.extractMin();
        extract_min_count++;
        out += std::to_string(result);
        out += "\t\\\\ result for ";
        out += nth(extract_min_count);
        out += "extract-min operation\n";
    }

    return out;
}




std::string Instructions::executeAVL(char* instruction, int parameter, AVL<int> *&tree) {
    std::string out = "";
    if (strcmp(instruction, "IN") == 0) { AVL<int>::insert(tree, parameter); }
    else if (strcmp(instruction, "MI") == 0) { out = tree->min() ? std::to_string(tree->min()->getKey()) : "None";}
    else if (strcmp(instruction, "MA") == 0) { out = tree->max() ? std::to_string(tree->max()->getKey()) : "None"; }
    else if (strcmp(instruction, "SC") == 0) { out = tree->successor(parameter) ?
        std::to_string(tree->successor(parameter)->getKey()) : "None"; }
    else if (strcmp(instruction, "PR") == 0) { out = tree->predecessor(parameter) ?
        std::to_string(tree->predecessor(parameter)->getKey()) : "None"; }
    else if (strcmp(instruction, "SE") == 0) { out = tree->select(parameter) ? std::to_string(tree->select(parameter)->getKey()) : "None"; }
    else if (strcmp(instruction, "SR") == 0) { out = tree->search(parameter) ? "true" : "false"; }
    else if (strcmp(instruction, "RA") == 0) { out = std::to_string(tree->rank(parameter)); }
    else if (strcmp(instruction, "TR") == 0) { out = tree->inorder(); }
    else { out += "Symbol out of specification."; }

    return out;
}


}
