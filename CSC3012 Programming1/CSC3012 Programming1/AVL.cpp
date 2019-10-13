//
//  AVL.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "AVL.hpp"



void AVL::insert(Value key) {
    insert(root, key);
}


bool AVL::search(Value key) {
    for (Node *current = root; current != nullptr; current = (key < current->key) ? current->left : current->left) {
        if (current->key == key) return true;
    }
    return false;
}

void AVL::printInorder() {
    Node* current = root;
    std::stack<Node*> stack;

    while (current || !stack.empty()) {
        while (current) {
            stack.push(current);
            current = current->left;
        }
        current = stack.top();
        stack.pop();
        std::cout << current->key << " ";
        current = current->right;
    }
    std::cout << "\n";
}

Value AVL::min() {
    if (root == nullptr) throw nullptr;
    Node* current = root;
    while (current->left != nullptr) current = current->left;
    return current->key;
}

Value AVL::max()  {
    if (root == nullptr) throw nullptr;
    Node* current = root;
    while (current->right != nullptr) current = current->right;
    return current->key;
}

int AVL::insert(Node* &root, Value key) {
    int imbalance;
    if (root == nullptr) {
        root = new Node(key);
        return 1;
    }

    if (key < root->key) {
        imbalance = -insert(root->left, key);
    } else {
        imbalance = insert(root->right, key);
    }

    if (imbalance == 0) {
        return 0;
    }

    root->balanceFactor += imbalance;
    rebalance(root);
    return (root->balanceFactor == 0) ? 0 : 1;
}


void AVL::rebalance(Node* &root) {
    if (root->balanceFactor == 2) {
        if (root->right->balanceFactor >= 0) {
            rotateLeft(root);
        } else {
            rotateRightLeft(root);
        }
    }

    if (root->balanceFactor == -2) {
        if (root->left->balanceFactor <= 0) {
            rotateRight(root);
        } else {
            rotateLeftRight(root);
        }
    }
}

void AVL::rotateRight(Node* &root) {
    Node* pivot = root->left;
    root->left = pivot->right;
    pivot->right = root;

    int rootBalance = root->balanceFactor;
    int pivotBalance = pivot->balanceFactor;

    if (pivot->balanceFactor >= 0) {
        root->balanceFactor = rootBalance - pivotBalance - 1;
    } else {
        root->balanceFactor = rootBalance - 1;
    }

    if (root->balanceFactor <= 0) {
        pivot->balanceFactor = pivotBalance + root->balanceFactor -1;
    } else {
        pivot->balanceFactor = pivotBalance + 1;
    }

    root = pivot;
}

void AVL::rotateLeft(Node* &root) {
    Node *pivot = root->right;
    root->right = pivot->left;
    pivot->left = root;

    int rootBalance = root->balanceFactor;
    int pivotBalance = pivot->balanceFactor;

    if (pivot->balanceFactor >= 0) {
        root->balanceFactor = rootBalance - pivotBalance - 1;
    } else {
        root->balanceFactor = rootBalance - 1;
    }

    if (root->balanceFactor <= 0) {
        pivot->balanceFactor = pivotBalance + root->balanceFactor -1;
    } else {
        pivot->balanceFactor = pivotBalance + 1;
    }


    root = pivot;
}

void AVL::rotateLeftRight(Node* &root) {
    rotateLeft(root);
    rotateRight(root);
}

void AVL::rotateRightLeft(Node* &root) {
    rotateRight(root);
    rotateLeft(root);
}
