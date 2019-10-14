//
//  main.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "AVL.hpp"
#include <iostream>

void Heap_Tests() {
    // todo
}

void AVL_Tests() {
    AVL<int> *batch = new AVL<int>(0);
    AVL<float> *tree = new AVL<float>(3.14);

    for (int i = 0; i < 300; i++) {
        AVL<int>::insert(batch, i);
    }

    for (int i = 0; i < (300 - 1); i++) {
        if (batch->successor(i)->getKey() != i+1) {
            throw "Successor function is broken.";
        }
    }

    for (int i = 0; i < 30; i++) {
        AVL<float>::insert(tree, i * 7.0);
    }

    std::cout << tree->inorder() << "\n";
    std::cout << "find 63: " << (tree->search(63) ? "true" : "false") << "\n";
    std::cout << "find 4000: " << (tree->search(4000) ? "true" : "false") << "\n";
    std::cout << "min: " << tree->min()->getKey() << "\n";
    std::cout << "max: " << tree->max()->getKey() << "\n";

    std::cout << "successor 64: " << (tree->successor(63)->getKey()) << "\n";
    std::cout << "successor 28: " << (tree->successor(28)->getKey()) << "\n";
    std::cout << "successor 77: " << (tree->successor(77)->getKey()) << "\n";

    std::cout << "rank 77: " << (tree->rank(77)) << "\n";
    std::cout << "select 13: " << (tree->select(13)->getKey()) << "\n";
}

int main(int argc, const char * argv[]) {
    AVL_Tests();
    Heap_Tests();
    return 0;
}
