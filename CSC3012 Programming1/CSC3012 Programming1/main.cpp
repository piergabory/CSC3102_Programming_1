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

    for (int i = 0; i < 100; i++) {
        tree.insert(i);
    }

    tree.printInorder();

    std::cout << "find 3: " << (tree.search(3) ? "true" : "false") << "\n";
    std::cout << "find 4000: " << (tree.search(4000) ? "true" : "false") << "\n";

    try {
        std::cout << "min: " << tree.min() << "\n";
        std::cout << "max: " << tree.max() << "\n";
    } catch(std::nullptr_t error) {
        std::cerr << "Error: empty tree\n";
    }

    return 0;
}
