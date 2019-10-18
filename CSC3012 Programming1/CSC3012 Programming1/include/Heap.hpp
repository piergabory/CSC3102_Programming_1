//
//  Heap.hpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory and Wasim Alam on 11/10/2019.
//
//

#ifndef Heap_h
#define Heap_h

#include <vector>

namespace CSC3012_P1 {

/**
 * @brief C++ K-ary heap structure implementation
 */
template <typename T>
class Heap {
    /// Number of branches per nodes.
    const size_t K;

    /// Array representation of the heap.
    std::vector<T> arrayRep;
    
public:

    /// Constructor
    Heap() : K(2) {}

    /// Destructor
    Heap(const size_t k): K(k) {}

    /**
     * @brief Heap insertion
     *
     * add the new value at the end of the array.
     * the new node starts as the last leaf of the heap.
     * we then iteratively bubble up the value to its parent,
     * until the heap property is restored
     *
     * @param value to insert.
     */
    void insert(T value) {
        arrayRep.push_back(value);

        // restore heap
        size_t parent, current = arrayRep.size();
        while (current >= K) {
            parent = current / K;
            if (get(current) > get(parent)) {
                return;
            }
            swap(get(current), get(parent));
            current = parent;
        }
    }

    /**
     * @brief Heap MIN-extraction
     *
     * 1. Swap the root and last leaf.
     * 2. Restore the heap property, ignoring the last leaf
     * 3. Pop and return the last leaf from the array representation
     *
     * @return the smallest value of the heap.
     */
    T extractMin() {
        swap(first(), last());

        // restore heap poperty.

        // going down, from the root to the leaf.
        size_t current = 1;
        while (current < arrayRep.size()) {

            // find the smallest child of the current node.
            size_t min_child = current + 1;
            for (size_t offset = 1; offset <= K && (current + offset) < arrayRep.size(); offset++) {
                min_child = (get(current + offset) < get(min_child)) ? (current + offset) : min_child;
            }

            // if the node is smaller then the min_child. The local heap is restored.
            if (get(min_child) > get(current)) {
                break;
            }

            // else swap current and min values and repeat down on the min_child
            else {
                swap(get(current), get(min_child));
                current = min_child * K;
            }
        }

        // pop and return.
        const int min = last();
        arrayRep.pop_back();
        return min;
    }

private:

    /// returrns the R valuee of the root of the heap
    inline T& first() {
        return arrayRep[0];
    }

    /// return the R value of the last leaf of the heap
    inline T& last() {
        return arrayRep[arrayRep.size() - 1];
    }


    /// R-value Getter translating operations on the array with indexes starting at 1.
    /// Simplifiies math.
    inline T& get(size_t index) {
        return arrayRep[index - 1];
    }

    /// Swap 2 R-values
    static inline void swap(T &lhs, T &rhs) {
        T tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }
};

}

#endif /* Heap_h */
