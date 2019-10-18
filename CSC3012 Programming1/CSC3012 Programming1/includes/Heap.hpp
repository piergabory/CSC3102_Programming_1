//
//  Heap.hpp
//  CSC3012 Programming1
//
//  Created by Pierre Gabory on 11/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#ifndef Heap_h
#define Heap_h

#include <vector>

template <typename T>
class Heap {
    const int K;
    std::vector<T> arrayRep;
    
public:
    Heap() : K(2) {}
    Heap(const int k): K(k) {}

    void insert(T value) {
        arrayRep.push_back(value);
        size_t parent, current = arrayRep.size();
        while (current != 0) {
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

        int current = 1;
        while (current < arrayRep.size()) {
            int min_child = current + 1;
            for (int offset = 1; offset <= K && (current + offset) < arrayRep.size(); offset++) {
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

#endif /* Heap_h */
