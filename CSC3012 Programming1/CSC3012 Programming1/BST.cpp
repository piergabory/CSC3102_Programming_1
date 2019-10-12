//
//  BST.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "BST.hpp"

BST::BST(Value root) : value(root) {}

BST::~BST() {
    delete left;
    delete right;
}


void BST::insert(Value newValue) {
    insert(new BST(newValue));
}

void BST::insert(BST* node) {
    if (node->value < value) {
        if (left) {
            left->insert(node);
        } else {
            left = node;
        }
    } else {
        if (right) {
            right->insert(node);
        } else {
            right = node;
        }
    }
}

void BST::printInorder() {
    if (left) left->printInorder();
    std::cout << value << " ";
    if (right) right->printInorder();
}

bool BST::search(Value value) {
    BST* cursor = this;
    while (cursor) {
        if (value == cursor->value) {
            return true;
        }

        if (cursor->value < value) {
            cursor = cursor->left;
        } else {
            cursor = cursor->right;
        }
    }
    return false;
}

Value BST::min() {
    BST* cursor = this;
    while (cursor->left) {
        cursor = cursor->left;
    }
    return cursor->value;
}

Value BST::max() {
    BST* cursor = this;
    while (cursor->right) {
        cursor = cursor->right;
    }
    return cursor->value;
}
