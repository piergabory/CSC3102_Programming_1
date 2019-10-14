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
typedef unsigned int Rank;

class AVL {
public:
    inline void insert(Value key) { insert(root, key); }
    bool search(Value key);
    void printInorder();
    Value min();
    Value max();
    Value successor(Value value);
    Rank rank(Value key) { return rank(root, key); }
    Value select(Rank index)  { return select(root, index)->key; }

private:
    struct Node {
        Value key;
        int balanceFactor = 0;
        unsigned int size = 0;
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

    static Node* select(Node* root, Rank rank);
    static Rank rank(Node* root, Value rank);
};

#endif /* AVL_Tree_h */
