//
//  AVL_Tree.hpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef AVL_Tree_h
#define AVL_Tree_h

typedef int Value;

class AVL {
    void insert(Value value);

    bool search(Value value);

    Value select(unsigned long index);

    unsigned long rank(Value value);

    Value min();

    Value max();

    void printInorder();
}

#endif /* AVL_Tree_h */
