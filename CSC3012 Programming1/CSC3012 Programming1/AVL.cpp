//
//  AVL.cpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "AVL.hpp"

bool AVL::search(Value key) {
    Node *current = root;
    while (current != nullptr) {
        if (current->key == key) return true;
        current = (key < current->key) ? current->left : current->right;
    }
    return false;
}

std::string AVL::inorder() {
    Node* current = root;
    std::stack<Node*> stack;
    std::string output = "";
    while (current || !stack.empty()) {
        while (current) {
            stack.push(current);
            current = current->left;
        }
        current = stack.top();
        stack.pop();
        output += std::to_string(current->key) + " ";
        current = current->right;
    }

    return output;
}

Value AVL::min() {
    if (root == nullptr) throw EmptyTreeError();
    Node* current = root;
    while (current->left != nullptr) current = current->left;
    return current->key;
}

Value AVL::max()  {
    if (root == nullptr) throw EmptyTreeError();
    Node* current = root;
    while (current->right != nullptr) current = current->right;
    return current->key;
}

Value AVL::successor(Value key) {
    bool goingLeft;
    Node *current = root, *adjacent = root;

    // classic iterative search. If we branch left, we keep a pointer to the parent.
    while (current) {
        // Finds the key
        if (current->key == key) {
            // if the key has a right child,
            if (current->right) {
                // the successor is in the min of the right subtree.
                adjacent = current->right;
                // classic min
                while (adjacent->left != nullptr) {
                    adjacent = adjacent->left;
                }
            }
            // else the successor is the last parent where we branched left.
            return adjacent->key;
        }

        goingLeft = key < current->key;
        if (goingLeft) adjacent = current;
        current = goingLeft ? current->left : current->right;
    }
    throw KeyNotFoundError();
}

AVL::Node* AVL::select(Node *root, unsigned int rank) {
    if (root == nullptr) throw EmptyTreeError();
    unsigned int leftSize = root->left ? root->left->size : 0;
    if (leftSize >= rank) {
        return select(root->left, rank);
    }
    if (leftSize + 1 == rank) {
        return root;
    }
    return select(root->right, rank - 1 - leftSize);
}


Rank AVL::rank(Node *root, Value key) {
    if (root == nullptr) return 0;
    if (key < root->key) return rank(root->left, key);
    if (key == root->key) return (root->left ? root->left->size : 0) + 1;
    return root->left->size + 1 + rank(root->right, key); // Segfault here means the size proprety isn't maintained properly. todo: Fix Lrotate/Rrotate size property.
}


int AVL::insert(Node* &root, Value key) {
    int imbalance;
    if (root == nullptr) {
        root = new Node(key);
        return 1;
    }

    // discard duplicates
    if (root->key == key) {
        return 0;
    }

    root->size++;

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
