#include "deque.h"

// Constructor
Deque::Deque(size_t block_size)
    : block_size(block_size), blockmap_capacity(4), front_index(block_size * 2), back_index(block_size * 2), element_count(0) {
    blockmap = new int*[blockmap_capacity]();
    for (size_t i = 0; i < blockmap_capacity; i++) {
        blockmap[i] = nullptr;
    }
}

// Destructor
Deque::~Deque(){
    for (size_t i = 0; i < blockmap_capacity; i++) {
        delete[] blockmap[i];
    }
    delete[] blockmap;
}

// Internal method to reallocate the blockmap
void Deque::reallocate_map(size_t new_capacity) {
    int** new_blockmap = new int*[new_capacity]();
    size_t offset = (new_capacity - blockmap_capacity) / 2;

    for (size_t i = 0; i < blockmap_capacity; i++) {
        new_blockmap[offset + i] = blockmap[i];
    }

    delete[] blockmap;
    blockmap = new_blockmap;
    blockmap_capacity = new_capacity;


    front_index += offset * block_size;
    back_index += offset * block_size;
}

// Internal method to allocate a new block if needed
void Deque::reallocate_block(size_t block) {
    if (blockmap[block] == nullptr) {
        blockmap[block] = new int[block_size]();
    }
}

// Push to the front
void Deque::push_front(int value) {
    if (front_index == 0) {
        reallocate_map(blockmap_capacity * 2);
    }

    front_index--;
    size_t block = front_index / block_size;
    size_t offset = front_index % block_size;

    reallocate_block(block);
    blockmap[block][offset] = value;
    ++element_count;
}

// Push to the back
void Deque::push_back(int value) {
    if (back_index == blockmap_capacity * block_size) {
        reallocate_map(blockmap_capacity * 2);
    }

    size_t block = back_index / block_size;
    size_t offset = back_index % block_size;

    reallocate_block(block);
    blockmap[block][offset] = value;
    back_index++;
    element_count++;
}

// Pop from the front
void Deque::pop_front() {
    size_t block = front_index / block_size;
    size_t offset = front_index % block_size;

    blockmap[block][offset] = 0; // Optional: Reset value
    front_index++;
    element_count--;
}

// Pop from the back
void Deque::pop_back() {
    back_index--;
    size_t block = back_index / block_size;
    size_t offset = back_index % block_size;

    blockmap[block][offset] = 0; // Optional: Reset value
    element_count--;
}

// Get the front element
int Deque::front() const {
    size_t block = front_index / block_size;
    size_t offset = front_index % block_size;

    return blockmap[block][offset];
}

// Get the back element
int Deque::back() const {
    if (empty()) {
        throw out_of_range("Deque is empty.");
    }

    size_t block = (back_index - 1) / block_size;
    size_t offset = (back_index - 1) % block_size;

    return blockmap[block][offset];
}

// Check if the deque is empty
bool Deque::empty() const {
    return element_count == 0;
}

// Get the size of the deque
size_t Deque::size() const {
    return element_count;
}

// Access element by index
int& Deque::operator[](size_t index) {
    size_t actual_index = front_index + index;
    size_t block = actual_index / block_size;
    size_t offset = actual_index % block_size;

    return blockmap[block][offset];
}
