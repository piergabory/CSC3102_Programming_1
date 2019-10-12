//
//  AVL.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "AVL.hpp"

AVL::AVL(Value value): BST(value) {}

void AVL::insert(Value value) {
    BST::insert(new AVL(value));
}

