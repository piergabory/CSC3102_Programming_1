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
        const T min = first();
        swap(first(), last());
        arrayRep.pop_back();

        size_t next, current = 1;
        while (current < arrayRep.size()) {
            next = current * K;

            bool validHeap = true;
            for (size_t i = 0; i < K; i++) {
                validHeap &= get(current) < get(next + 1);
            }
            if (validHeap) return min;

            size_t min_child_index = next;
            for (size_t i = 0; i < K; i++) {
                min_child_index = ( get(next) < get(min_child_index) ) ? next : min_child_index;
            }
            next = min_child_index;

            swap(get(current), get(next));
            current = next;
        }

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
