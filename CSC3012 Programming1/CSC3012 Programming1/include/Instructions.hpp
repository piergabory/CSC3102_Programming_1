//
//  input.hpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 17/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef input_hpp
#define input_hpp

#include <cstring>
#include <cstdio>

#include <iostream>
#include <string>
#include <typeinfo>

#include "AVL.hpp"
#include "Heap.hpp"
//#include "timer.hpp"


class Instructions {
    FILE* input;
    std::string buffer;
    unsigned int extract_min_count;

public:
    Instructions(std::string filename);
    ~Instructions();
    void executeForAVL();
    void executeForHeap();
    void saveTo(std::string filename);

private:
    std::string getNextInstruction(char instruction[], int &integer);
    std::string executeHeap(char* instruction, int parameter, Heap<int> &heap);
    std::string executeAVL(char* instruction, int parameter, AVL<int> *&tree);
};


#endif /* input_hpp */
