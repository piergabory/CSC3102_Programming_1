//
//  AVL.hpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 14/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef AVL_hpp
#define AVL_hpp

#include <algorithm>
#include <string>

template<typename T>
class AVL {
    const T _key;
    int height = 0;
    int size = 1;
    AVL<T> *left = nullptr;
    AVL<T> *right = nullptr;

public:

    AVL(T key): _key(key) {}

    ~AVL() { delete left; delete right; }

    inline T getKey() {
        return _key;
    }

    std::string inorder() {
        std::string string = "";
        if (left) {
            string += left->inorder();
        }
        string += std::to_string(getKey()) + " ";
        if (right) {
            string += right->inorder();
        }
        return string;
    }

    bool search(T value) {
        AVL<T> *current = this;
        while (current) {
            if (value == current->getKey()) {
                return true;
            }

            if (value < current->getKey()) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

    AVL<T>* min() {
        AVL<T> *current = this;
        while (current->left) {
            current = current->left;
        }
        return current;
    }

    AVL<T>* max() {
        AVL<T> *current = this;
        while (current->right) {
            current = current->right;
        }
        return current;
    }

    AVL<T>* successor(T value) {
        bool found = false;
        AVL<T> *current = this, *lastSuperiorParent = nullptr;

        while (current) {
            if (value == current->getKey()) {
                found = true;
                if (current->right) {
                    return current->right->min();
                }
            }

            if (value < current->getKey()) {
                lastSuperiorParent = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (found) {
            return lastSuperiorParent; // Null if no successors.
        } else {
            return nullptr;
        }
    }

    AVL<T>* select(unsigned int rank) {
        int leftSize = left ? left->size : 0;
        if (leftSize >= rank) {
            return left->select(rank);
        }
        if (leftSize + 1 == rank) {
            return this;
        }
        return right->select(rank - leftSize -  1);
    }

    unsigned int rank(T key) {
        unsigned int leftRank = left ? left->rank(key) : 0;
        unsigned int rightRank = right ? right->rank(key) : 0;
        unsigned int leftSize = (left ? left->size : 0);

        if (key < getKey()) return leftRank;
        if (key == getKey()) return leftSize + 1;
        return leftSize + 1 + rightRank;
    }

    static int insert(AVL *&node, T key) {
        int imbalance;
        if (node == nullptr) {
            node = new AVL<T>(key);
            return 1;
        }

        // discard duplicates
        if (node->getKey() == key) {
            return 0;
        }

        if (key < node->getKey()) {
            imbalance = -insert(node->left, key);
        } else {
            imbalance = insert(node->right, key);
        }

        node->size++;

        if (imbalance == 0) {
            return 0;
        }

        rebalance(node);
        return (node->balanceFactor() == 0) ? 0 : 1;
    }

    private:

    inline int balanceFactor() {
        return (right ? right->height : 0) - (left ? left->height : 0);
    }

    static void rebalance(AVL *&node) {
        if (node->balanceFactor() == 2) {
            if (node->right->balanceFactor() >= 0) {
                rotateLeft(node);
            } else {
                rotateRightLeft(node);
            }
        }

        if (node->balanceFactor() == -2) {
            if (node->left->balanceFactor() <= 0) {
                rotateRight(node);
            } else {
                rotateLeftRight(node);
            }
        }
    }

    static void rotateRight(AVL *&node) {
        AVL* pivot = node->left;
        node->left = pivot->right;
        pivot->right = node;

        // update size property
        pivot->size += (node->right ? node->right->size : 0) + 1;
        node->size -= (pivot->left ? pivot->left->size : 0) + 1;

        // update height property
        node->height = std::max(node->left->height, node->right->height);
        pivot->height = std::max(pivot->left->height, pivot->right->height);


        node = pivot;
    }

    static void rotateLeft(AVL *&node) {
        AVL *pivot = node->right;
        node->right = pivot->left;
        pivot->left = node;

        // update size property
        pivot->size += (node->left ? node->left->size : 0) + 1;
        node->size -= (pivot->right ? pivot->right->size : 0) + 1;

        node->height = std::max(node->left->height, node->right->height);
        pivot->height = std::max(pivot->left->height, pivot->right->height);

        node = pivot;
    }

    inline static void rotateLeftRight(AVL *&node) {
        rotateLeft(node->left);
        rotateRight(node);
    }

    inline static void rotateRightLeft(AVL *&node) {
        rotateRight(node->right);
        rotateLeft(node);
    }
};


#endif /* AVL_hpp */
