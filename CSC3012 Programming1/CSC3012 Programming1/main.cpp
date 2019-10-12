//
//  main.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "BST.hpp"

int main(int argc, const char * argv[]) {

    BST tree(6);

    tree.insert(1);
    tree.insert(4);
    tree.insert(8);
    tree.insert(9);

    tree.printInorder();

    std::cout << "\n";
    std::cout << "find 3: " << tree.search(3) << "\n";
    std::cout << "find 4: " << tree.search(4) << "\n";
    std::cout << "min: " << tree.min() << "\n";
    std::cout << "max: " << tree.max() << "\n";

    return 0;
}
