#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <stdint.h>
#endif

template <size_t Capacity>
#ifdef ARDUINO
class RingBuffer : public Stream {
#else
class RingBuffer {
#endif
public:
    RingBuffer() : head_(0), tail_(0), count_(0) {}

    size_t write(uint8_t item) {
        if (isFull()) {
            return 0;
        }
        buffer_[head_] = item;
        head_ = (head_ + 1) % Capacity;
        count_++;
        return 1;
    }

    int available() {
        return count_;
    }

    int availableForWrite() {
        return Capacity - count_;
    }

    int read() {
        if (isEmpty()) {
            return -1;
        }
        uint8_t item = buffer_[tail_];
        tail_ = (tail_ + 1) % Capacity;
        count_--;
        return item;
    }

    int peek() {
        if (isEmpty()) {
            return -1;
        }
        return buffer_[tail_];
    }

    bool isEmpty() const {
        return count_ == 0;
    }

    bool isFull() const {
        return count_ == Capacity;
    }

    size_t size() const {
        return count_;
    }

    void clear() {
        head_ = tail_ = count_ = 0;
    }

#ifdef ARDUINO
    void flush() {}
#endif
protected:
    uint8_t buffer_[Capacity];
    size_t head_;
    size_t tail_;
    size_t count_;
};
