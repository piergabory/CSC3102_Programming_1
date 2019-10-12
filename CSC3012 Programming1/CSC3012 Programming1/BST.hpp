//
//  BST.hpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef BST_hpp
#define BST_hpp

#include <iostream>

typedef int Value;

class BST {
public:
    void insert(Value value);

    bool search(Value value);

    Value min();

    Value max();

    void printInorder();

    BST(Value root);
    
    ~BST();

protected:
    BST* left = nullptr;

    BST* right = nullptr;
    
    Value value;

    void insert(BST* node);
};

#endif /* BST_hpp */
