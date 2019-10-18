//
//  AVL.hpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory and Wasim alam on 14/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef AVL_hpp
#define AVL_hpp

#include <algorithm>
#include <string>

namespace CSC3012_P1 {

/**
 * # AVL Tree class
 * CPP Implementation of AVL trees.
 * Template class can handle any type implementing the > and == operator
 */
template<typename T>
// -MARK : Private properties
class AVL {

    /// Constant property, value of the node
    const T _key;


    /// Height of the tree, length of the longest path in the tree
    int height;


    /// Number of nodes in the tree, including the root.
    int size;


    /// Pointer towards the left and right subtree.
    /// The left subtree contains all the values lower than the root's key.
    /// The right subtree contains all the values higher than the root's key.
    AVL<T> *left;
    AVL<T> *right;

// -MARK : Public methods
public:

    /// Constructor: initialize the key.
    AVL(T key):
        _key(key),
        height(0),
        size(1),
        left(nullptr),
        right(nullptr)
    {}



    /// Destructor: Recursively deletes its childrens.
    ~AVL() { delete left; delete right; }



    /// Key value getter.
    inline T getKey() {
        return _key;
    }



    /**
     * @brief In-order stringification of the tree.
     * Concatenates all the values of the tree in in-order in a space separated values string: "A B C D E F"
     *
     * We choosed a recursive solution for simplicity. An iterative solution could be done with a stack structure.
     *
     * @returns string representation of the tree
     */
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



    /**
     * @brief tells if a value is present in the AVL tree.
     *
     * Iterative solution of the AVL search algorithm
     *
     * @param value  needle searched in the tree's haystack of nodes.
     * @returns boolean, true if the value is present in the tree
     */
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



    /**
     * @brief returns the tree's node with the smallest key
     * Implemented with iterative solution
     * @returns the leftmost node of the AVL tree
     */
    AVL<T>* min() {
        AVL<T> *current = this;
        while (current->left) {
            current = current->left;
        }
        return current;
    }



    /**
     * @brief returns the tree's node with the largest key
     * Implemented with iterative solution
     * @returns the rightmost node of the AVL tree
     */
    AVL<T>* max() {
        AVL<T> *current = this;
        while (current->right) {
            current = current->right;
        }
        return current;
    }



    /**
     * @brief finds the successor to a value.
     * Iterative implementation
     * Will return the min() of the right subtree if it exists,
     * else will return the last parent where the node came branching left.
     *
     * @param value to success to.
     * @returns
     *      - the node with the smallest superior key to the provided value.
     *      - Null if the value there are no successors.
     */
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


    // Is that what PR are supposed to be?
    /// Predecessor, see Successor.
    AVL<T>* predecessor(T value) {
           bool found = false;
           AVL<T> *current = this, *lastInferiorParent = nullptr;

           while (current) {
               if (value == current->getKey()) {
                   found = true;
                   if (current->left) {
                       return current->left->max();
                   }
               }

               if (value < current->getKey()) {
                   current = current->left;
               } else {
                   lastInferiorParent = current;
                   current = current->right;
               }
           }

           if (found) {
               return lastInferiorParent; // Null if no successors.
           } else {
               return nullptr;
           }
       }



    /**
     * @brief finds the node matching the provided rank.
     * Recursive implementation.
     * Will return the rankth smallest node.
     * @param rank  searched rank
     * @return node matching the rank
     */
    AVL<T>* select(unsigned int rank) {
        unsigned int leftSize = left ? left->size : 0;
        if (leftSize >= rank) {
            return left->select(rank);
        }
        if (leftSize + 1 == rank) {
            return this;
        }
        return right->select(rank - leftSize -  1);
    }



    /**
     * @brief computes the rank of a key in a subtree.
     * Recursive implementation.
     * Will return the number of nodes with a value lower than the provided key.
     * @param key key of the searched node.
     * @return return the rank of the node
     */
    unsigned int rank(T key) {
        unsigned int leftRank = left ? left->rank(key) : 0;
        unsigned int rightRank = right ? right->rank(key) : 0;
        unsigned int leftSize = (left ? left->size : 0);

        if (key < getKey()) return leftRank;
        if (key == getKey()) return leftSize + 1;
        return leftSize + 1 + rightRank;
    }



    /**
     * @brief AVL insertion
     * BST insertion of a new node, with restoration of the AVL properties.
     * Recursive implementation
     * Insertions are cancelled if the key is already present in the tree.
     * @param node destination tree
     * @param key value of the created key.
     * @return absolute value of the tree's balance. used internally in the recursion.
     */
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


    // -MARK : Private methods
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

}

#endif /* AVL_hpp */
