//
//  main.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "Instructions.hpp"

int main(int argc, const char * argv[]) {
    Heap<2, int> heap2;
    Heap<3, int> heap3;
    Heap<4, int> heap4;
    Heap<6, int> heap6;
    Heap<10, int> heap10;

    for(int i = 1; i < 100; i++) {
        heap2.insert(((i * 47) / 3) % 13);
        heap3.insert(((i * 47) / 3) % 13);
        heap4.insert(((i * 47) / 3) % 13);
        heap6.insert(((i * 47) / 3) % 13);
        heap10.insert(((i * 47) / 3) % 13);

        if (i % 6 == 0) {
            heap2.extractMin();
            heap3.extractMin();
            heap4.extractMin();
            heap6.extractMin();
            heap10.extractMin();
        }
    }

    Instructions avl_instructions("AVLinput.txt");
    avl_instructions.executeForAVL();
    avl_instructions.saveTo("AVLoutput.txt");

    Instructions heap_instructions("HeapInput.txt");
    heap_instructions.executeForHeap();
    heap_instructions.saveTo("HeapOutput.txt");

    return 0;
}
