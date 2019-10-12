//
//  AVL.hpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef AVL_h
#define AVL_h

#include "BST.hpp"

class AVL: public BST {
public:
    void insert(Value value);

    unsigned int rank(Value value);

    Value select(unsigned int index);

    AVL(Value value);

private:
    int balance = 0;
};

#endif /* AVL_Tree_h */
