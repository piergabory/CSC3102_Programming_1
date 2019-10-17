//
//  main.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "AVL.hpp"
#include "Heap.hpp"
#include "input.hpp"

#include <iostream>


void Heap_Tests() {
    Heap<int> heap;

    for (int i = 30; i != 0 ; i--) {
        heap.insert(i);
    }

    for (int i = 30; i != 0 ; i--) {
        std::cout << heap.extractMin() << " ";
    }

    std::cout << "\n";
}

void AVL_Tests() {
    AVL<int> *batch = new AVL<int>(0);
    AVL<char> *tree = new AVL<char>('a');

    for (int i = 0; i < 300; i++) {
        AVL<int>::insert(batch, i);
    }

    for (int i = 0; i < (300 - 1); i++) {
        if (batch->successor(i)->getKey() != i+1) {
            throw "Successor function is broken.";
        }
    }

    for (int i = 0; i < 26; i++) {
        AVL<char>::insert(tree, i + 'a');
    }

    std::cout << tree->inorder() << "\n";
    std::cout << "find 'x': " << (tree->search('x') ? "true" : "false") << "\n";
    std::cout << "find 'X': " << (tree->search('X') ? "true" : "false") << "\n";
    std::cout << "min: " << tree->min()->getKey() << "\n";
    std::cout << "max: " << tree->max()->getKey() << "\n";

    std::cout << "successor 'a': " << (tree->successor('a')->getKey()) << "\n";
    std::cout << "successor 'x': " << (tree->successor('x')->getKey()) << "\n";
    std::cout << "successor 'm': " << (tree->successor('m')->getKey()) << "\n";

    std::cout << "rank 'c': " << (tree->rank('c')) << "\n";
    std::cout << "select 3: " << (tree->select(3)->getKey()) << "\n";
}

int main(int argc, const char * argv[]) {
    AVL_Tests();
    Heap_Tests();

    Instructions avl_instructions("AVLinput.txt");
    avl_instructions.executeForAVL();

    Instructions heap_instructions("HeapInput.txt");
    heap_instructions.executeForHeap();

    return 0;
}
