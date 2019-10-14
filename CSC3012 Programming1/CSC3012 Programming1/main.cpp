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
    AVL batch, tree;

    for (int i = 0; i < 300; i++) {
        batch.insert(i);
    }

    for (int i = 0; i < (300 - 1); i++) {
        if (batch.successor(i) != i+1) {
            throw "Successor function is broken.";
        }
    }

    for (int i = 0; i < 30; i++) {
        tree.insert(i * 7);
    }

    std::cout << tree.inorder() << "\n";
    std::cout << "find 3: " << (tree.search(3) ? "true" : "false") << "\n";
    std::cout << "find 4000: " << (tree.search(4000) ? "true" : "false") << "\n";

    try {
        std::cout << "min: " << tree.min() << "\n";
        std::cout << "max: " << tree.max() << "\n";
    } catch(AVL::EmptyTreeError error) {
        std::cerr << "Error: empty tree\n";
    }

    try {
        std::cout << "successor 64: " << (tree.successor(63)) << "\n";
        std::cout << "successor 28: " << (tree.successor(28)) << "\n";
        std::cout << "successor 77: " << (tree.successor(77)) << "\n";
    } catch(AVL::KeyNotFoundError error) {
        std::cerr << "No successor\n";
    }

    try {
         std::cout << "rank 30: " << (tree.rank(30)) << "\n";
     } catch(AVL::EmptyTreeError x) {
         std::cerr << "Error: empty tree\n";
     }

     try {
         std::cout << "select 30: " << (tree.select(30)) << "\n";
     } catch(AVL::EmptyTreeError x) {
         std::cerr << "Error: empty tree\n";
     }
}

int main(int argc, const char * argv[]) {
    AVL_Tests();
    Heap_Tests();
    return 0;
}
