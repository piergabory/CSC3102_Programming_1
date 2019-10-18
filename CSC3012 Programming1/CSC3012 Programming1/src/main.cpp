//
//  main.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "TimeReport.hpp"
#include "Instructions.hpp"
#include <random>

int main(int argc, const char * argv[]) {
    TimeReport report;

    report.startRecording("AVL");
    Instructions avl_instructions("AVLinput.txt");
    avl_instructions.executeForAVL();
    avl_instructions.saveTo("AVLoutput.txt");
    report.stopRecording();

    report.startRecording("Heap");
    Instructions heap_instructions("HeapInput.txt");
    heap_instructions.executeForHeap();
    heap_instructions.saveTo("HeapOutput.txt");
    report.stopRecording();

    std::cout << report.report();


    TimeReport kHeapTimes;
    for (int i = 2; i < 30; i++) {
        kHeapTimes.startRecording("Heap K=" + std::to_string(i));
        for(int j = 3; j < 100; j++) {
            Heap<int> heap(i);
            for(int j = 3; j < 100; j++) {
                heap.insert(rand());
                if (j % 10 == 0) {
                    heap.extractMin();
                }
            }
        }
        kHeapTimes.stopRecording();
    }
    std::cout << kHeapTimes.report();

    return 0;
}
