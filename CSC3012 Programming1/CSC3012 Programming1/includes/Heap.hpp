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
    std::vector<T> arrayRep;

    public:
    void insert(T value) {
        arrayRep.push_back(value);
        size_t parent, current = arrayRep.size();
        while (current != 0) {
            parent = current / 2;
            if (get(current) > get(parent)) {
                return;
            }
            swap(get(current), get(parent));
            current = parent;
        }
    }

    T extractMin() {
        const T min = arrayRep.front();
        swap(arrayRep.front(), arrayRep.back());
        arrayRep.pop_back();

        size_t next, current = 1;
        while (current < arrayRep.size()) {
            next = current * 2;
            if (get(current) < get(next) && get(current) < get(next + 1)) {
                break;
            }
            next += get(next) > get(next + 1);
            swap(get(current), get(next));
            current = next;
        }

        return min;
    }

private:
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
