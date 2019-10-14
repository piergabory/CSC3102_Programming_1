//
//  main.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "AVL.hpp"

int main(int argc, const char * argv[]) {
    AVL tree;

    std::cout << "rank 30: " << (tree.rank(30)) << "\n";
    try {
        std::cout << "select 30: " << (tree.select(30)) << "\n";
    } catch(AVL::EmptyTreeError error) {
        std::cerr << "Error: empty tree\n";
    }

    for (int i = 0; i < 100; i++) {
        tree.insert(i);
    }

    tree.printInorder();

    std::cout << "find 3: " << (tree.search(3) ? "true" : "false") << "\n";
    std::cout << "find 4000: " << (tree.search(4000) ? "true" : "false") << "\n";

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

    try {
        std::cout << "min: " << tree.min() << "\n";
        std::cout << "max: " << tree.max() << "\n";
    } catch(AVL::EmptyTreeError error) {
        std::cerr << "Error: empty tree\n";
    }


    try {
        for (int i = 0; i < 99; i++) {
            if (tree.successor(i) != i+1) {
                throw "Nope";
            }
        }
        std::cout << "successor 31: " << (tree.successor(31)) << "\n";
        std::cout << "successor 63: " << (tree.successor(63)) << "\n";
        std::cout << "successor 72: " << (tree.successor(72)) << "\n";
    } catch(AVL::KeyNotFoundError error) {
        std::cerr << "No successor\n";
    }

    return 0;
}
