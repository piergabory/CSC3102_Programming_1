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
#include <typeinfo>

#include "AVL.hpp"
#include "Heap.hpp"

class Instructions {
    FILE* file;

public:
    Instructions(std::string filename);
    ~Instructions();
    void executeForAVL();
    void executeForHeap();

private:
    void getNextInstruction(char instruction[], int &integer);
    static void executeHeap(char* instruction, int parameter, Heap<int> &heap);
    static void executeAVL(char* instruction, int parameter, AVL<int> *&tree);
};


#endif /* input_hpp */
