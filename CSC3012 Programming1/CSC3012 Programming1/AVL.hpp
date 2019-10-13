//
//  AVL.hpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef AVL_h
#define AVL_h

#include <iostream>
#include <stack>

typedef int Value;

class AVL {
public:
    void insert(Value key);
    bool search(Value key);
    void printInorder();
    Value min();
    Value max();
    unsigned int rank(Value key);
    Value select(unsigned int index);


private:
    struct Node {
        Value key;
        int balanceFactor = 0;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(Value key): key(key) {}
        ~Node() { delete left; delete right; }
    };
    Node* root = nullptr;

    static int insert(Node* &destination, Value value);
    static void rebalance(Node* &root);

    static void rotateLeft(Node* &root);
    static void rotateLeftRight(Node* &root);

    static void rotateRight(Node* &root);
    static void rotateRightLeft(Node* &root);
};

#endif /* AVL_Tree_h */
