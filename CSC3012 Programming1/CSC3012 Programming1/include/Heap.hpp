//
//  Heap.hpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory and Wasim alam on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef Heap_h
#define Heap_h

#include <vector>

namespace CSC3012_P1 {

template <typename T>
class Heap {
    const size_t K;
    std::vector<T> arrayRep;
    
public:
    Heap() : K(2) {}
    Heap(const size_t k): K(k) {}

    void insert(T value) {
        arrayRep.push_back(value);
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

    T extractMin() {
        swap(first(), last());

        size_t current = 1;
        while (current < arrayRep.size()) {
            size_t min_child = current + 1;
            for (size_t offset = 1; offset <= K && (current + offset) < arrayRep.size(); offset++) {
                min_child = (get(current + offset) < get(min_child)) ? (current + offset) : min_child;
            }

            if (get(min_child) > get(current)) {
                break;
            } else {
                swap(get(current), get(min_child));
                current = min_child * K;
            }
        }

        const int min = last();
        arrayRep.pop_back();
        return min;
    }

private:
    inline T& first() {
        return arrayRep[0];
    }

    inline T& last() {
        return arrayRep[arrayRep.size() - 1];
    }

    inline T& get(size_t index) {
        return arrayRep[index - 1];
    }

    static inline void swap(T &lhs, T &rhs) {
        T tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }
};

}

#endif /* Heap_h */
