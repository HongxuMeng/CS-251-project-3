//
//  HeapPriorityQueue.hpp
//
//  Created by Wenjie Bai on 2/7/19.
//  Copyright © 2019 Wenjie Bai. All rights reserved.
//

#ifndef HeapPriorityQueue_hpp
#define HeapPriorityQueue_hpp

#include <stdio.h>
#include "NotImplementedException.hpp"
//throw NotImplementedException whenever you are asked to pop something from an empty container.
#include <vector>
using namespace std;


template <typename Item>
class HeapPriorityQueue {

private:
    int current_size;   // Number of elements in heap
    int current_capacity;  
    vector<Item> this_vector;   // The heap array


public:
    HeapPriorityQueue(int capacity) {
        current_size = 0;
        current_capacity = capacity;
        this_vector.resize(capacity);
    }



    bool empty() const {
        if (current_size == 0) {
            return true;
        } else {
            return false;
        }
    }



    const Item& min() const {
        if (empty()) {
            throw NotImplementedException("gg");
        } else {
            return this_vector[1];
        }
    }



    int size() {
        return current_size;
    }



    void insert(const Item& x) {
        Item node = x;

        if (current_size == 0) {
            this_vector.resize(current_capacity);
            this_vector.insert(this_vector.begin() + 1, node);
            current_size++;
            return;

        } else {
            current_size++;
            int index = current_size;
            this_vector.insert((this_vector.begin() + current_size), node);

            for (int i = 0; index > 1; i++) {
                if ((index % 2) == 0) { //Left
                    if ((this_vector[index] < this_vector[index + 1]) || (index == current_size)) {
                        node = this_vector[index];
                        goto Even;
                    } else {
                        node = this_vector[index + 1];
                        goto Odd;
                    }
                } else { //Right
                    if ((this_vector[index] < this_vector[index - 1]) || (index == current_size)) {
                        node = this_vector[index];
                        goto Odd;
                    } else {
                        node = this_vector[index - 1];
                        goto Even;
                    }
                }

                Even://偶数

                    if (this_vector[index / 2] > node) {
                        Item large = this_vector[index / 2];
                        this_vector[index / 2] = node;
                        this_vector[index] = large;
                        index = index / 2;
                        continue;
                    } else {
                        goto Inserted;
                    }



                Odd://奇数

                    if (this_vector[(index - 1) / 2] > node) {
                        Item large = this_vector[(index - 1) / 2];
                        this_vector[(index - 1) / 2] = node;
                        this_vector[index] = large;
                        index = (index - 1) / 2;
                        continue;
                    } else {
                        goto Inserted;
                    }
            }

        Inserted:


            if (current_size == this_vector.capacity()) {
                resize();
            }
        }
    }



    void removeMin() {

        if (current_size == 0) {
            throw NotImplementedException("Removing empty");
            return;

        } else if (current_size == 1) {
            this_vector.clear();
            current_size--;

        } else {
            int index = 1;
            this_vector[1] = this_vector[current_size];
            Item node = this_vector[1];
            this_vector.erase((this_vector.begin() + current_size));
            current_size--;

            for (int i = 0; index < current_size; i++) {
                if ((this_vector[index * 2] < this_vector[index * 2 + 1]) || ((this_vector[index * 2] > this_vector[index * 2 + 1]) && ((index * 2) == current_size))) {
                    if (this_vector[index * 2] < node) {
                        Item temp = this_vector[index * 2];
                        this_vector[index * 2] = node;
                        this_vector[index] = temp;
                        index = index * 2;
                        continue;

                    } else {
                        return;

                    }
                } else {
                    if ((this_vector[index * 2 + 1] < node) && ((index * 2 + 1) <= current_size)) {
                        Item temp = this_vector[index * 2 + 1];
                        this_vector[index * 2 + 1] = node;
                        this_vector[index] = temp;
                        index = index * 2 + 1;
                        continue;

                    } else {
                        return;

                    }
                }
            }
        }
    }

    void resize () {
        this_vector.resize(2 * this_vector.capacity());
    }



};
#endif /* HeapPriorityQueue_hpp */

