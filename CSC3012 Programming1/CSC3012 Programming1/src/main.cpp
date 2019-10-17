//
//  main.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "Instructions.hpp"

int main(int argc, const char * argv[]) {
    Instructions avl_instructions("AVLinput.txt");
    avl_instructions.executeForAVL();
    avl_instructions.saveTo("AVLoutput.txt");

    Instructions heap_instructions("HeapInput.txt");
    heap_instructions.executeForHeap();
    heap_instructions.saveTo("HeapOutput.txt");

    return 0;
}
