#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>

using namespace std;

class Deque {
private:
    int** blockmap;
    size_t block_size;
    size_t blockmap_capacity;
    size_t front_index, back_index;
    size_t element_count;

    void reallocate_map(size_t new_capacity);
    void reallocate_block(size_t block);

public:
    Deque(size_t block_size = 64);
    ~Deque();

    void push_front(int value);
    void push_back(int value);
    void pop_front();
    void pop_back();

    int front() const;
    int back() const;

    bool empty() const;
    size_t size() const;

    int& operator[](size_t index);
};

#endif
