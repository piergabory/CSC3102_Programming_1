//
//  main.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "Instructions.hpp"

int main(int argc, const char * argv[]) {
    Heap<int> heap2(2);
    Heap<int> heap3(3);
    Heap<int> heap4(4);
    Heap<int> heap6(6);
    Heap<int> heap10(10);

    for(int i = 3; i < 100; i++) {
        heap2.insert(i);
        heap3.insert(i);
        heap4.insert(i);
        heap6.insert(i);
        heap10.insert(i);

//        if (i % 6 == 0) {
//            heap2.extractMin();
//            heap3.extractMin();
//            heap4.extractMin();
//            heap6.extractMin();
//            heap10.extractMin();
//        }
    }

    Instructions avl_instructions("AVLinput.txt");
    avl_instructions.executeForAVL();
    avl_instructions.saveTo("AVLoutput.txt");

    Instructions heap_instructions("HeapInput.txt");
    heap_instructions.executeForHeap();
    heap_instructions.saveTo("HeapOutput.txt");

    return 0;
}
