//
//  main.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory and Wasim alam on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "TimeReport.hpp"
#include "Instructions.hpp"
#include <random>
#include <stack>

using namespace CSC3012_P1;

int main(int argc, const char * argv[]) {

    std::string AVL_input, heap_input;

    // - MARK: Get input files
    if (argc == 3) {
        AVL_input = std::string(argv[1]);
        heap_input = std::string(argv[2]);
    } else {
        std::cout << "Usage: \n" << argv[0] << " [AVL input file] [Binary-Heap input file]\n\n";
        AVL_input = "AVL_input.txt";
        heap_input = "Heap_input.txt";
    }
    
    // - MARK: Execute input files
    Instructions avl_instructions(AVL_input);
    avl_instructions.executeForAVL();
    avl_instructions.saveTo(AVL_input + ".output.txt");

    Instructions heap_instructions(heap_input);
    heap_instructions.executeForHeap();
    heap_instructions.saveTo(heap_input + ".output.txt");


    // - MARK: K-ARY HEAP INSERT/EXTRACT EFFICIENCY

    // For each K-ary heaps type where K going from 2 to 10.
    // We execute 1000 insertions of Random integers, a 1000 times (to smooth out the random)
    // Then do a 1000 extracts min on all 1000 heaps created.
    // There is a million operations made for each k-ary heap type. The time is averaged in a graph.
    // It would have been be pertty nice if I had multithreaded that.

    // RESULT: We can clearly see that Inserts are ~O(e^(-k)) and Extracts are O(k)
    // K-ary heaps can be more interesting than binary heaps depending on the application.
    // we can even think of dynamically choosing the next best K depending on the Inserts-to-extract-ratios of previous executions.

    TimeReport kHeapInsertTimes, kHeapExtractTimes;
    std::stack< Heap<int> > heaps;

    for (int i = 2; i <= 10; i++) {

        // Measuring Insertions
        kHeapInsertTimes.startRecording("Heap K=" + std::to_string(i) + " insert");
        for(int j = 0; j < 1000; j++) {
            Heap<int> heap(i);
            for(int k = 0; k < 1000; k++) {
                heap.insert(rand());
            }
            heaps.push(heap);
        }
        kHeapInsertTimes.stopRecording();

        // Measuring Extractions
        kHeapExtractTimes.startRecording("Heap K=" + std::to_string(i) + " extractMin");
        for(int j = 0; j < 1000; j++) {
            Heap<int> heap = heaps.top();
            for(int k = 0; k < 1000; k++) {
                heap.extractMin();
            }
            heaps.pop();
        }
        kHeapExtractTimes.stopRecording();

    }

    std::cout << "\n";
    std::cout << "# One million Insert operations on K-ary heaps\n";
    std::cout << kHeapInsertTimes.report() << "\n";
    std::cout << "# One million Extract-min operations on K-ary heaps\n";
    std::cout << kHeapExtractTimes.report() << "\n";


    // More science:


    // - MARK: OPTIMUM K FOR 1 EXTRACT FOR 1 RATIO


    // For a Inserts-to-extract-ratios of 1. The o(k) of the extract
    // catches up quickly with the efficient insertions.
    // The optimum k seems to over around 3 or 4.

    TimeReport timeReport5000, timeReport50000, timeReport500000;

    for (int i = 2; i <= 10; i++) {
        Heap<int> heap(i);
        timeReport5000.startRecording("k=" + std::to_string(i) + "-> 5000   in/ex");
        for (int j = 0; j <= 5000; j++) {
            heap.insert(rand());
        }
        for (int j = 0; j <= 5000; j++) {
            heap.extractMin();
        }
        timeReport5000.stopRecording();
        timeReport50000.startRecording("k=" + std::to_string(i) + "-> 50000  in/ex");
        for (int j = 0; j <= 50000; j++) {
            heap.insert(rand());
        }
        for (int j = 0; j <= 50000; j++) {
            heap.extractMin();
        }
        timeReport50000.stopRecording();
        timeReport500000.startRecording("k=" + std::to_string(i) + "-> 500000 in/ex");
        for (int j = 0; j <= 500000; j++) {
            heap.insert(rand());
        }
        for (int j = 0; j <= 500000; j++) {
            heap.extractMin();
        }
        timeReport500000.stopRecording();
    }

    std::cout << "# Performance with Insert/extract ratio = 1\n";
    std::cout << timeReport5000.report() << "\n";
    std::cout << timeReport50000.report() << "\n";
    std::cout << timeReport500000.report() << "\n";

    
    return 0;
}
