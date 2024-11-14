#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#endif

template <size_t Size>
#ifdef ARDUINO
class RingBuffer : public Stream {
#else
class RingBuffer {
#endif
public:
    RingBuffer() : head(0), tail(0), count(0) {}

    size_t write(uint8_t item) {
        if (isFull()) {
            return 0;
        }
        buffer[head] = item;
        head = (head + 1) % Size;
        count++;
        return 1;
    }

    int available() {
        return count;
    }

    int availableForWrite() {
        return Size - count;
    }

    int read() {
        if (isEmpty()) {
            return -1;
        }
        uint8_t item = buffer[tail];
        tail = (tail + 1) % Size;
        count--;
        return item;
    }

    int peek() {
        if (isEmpty()) {
            return -1;
        }
        return buffer[tail];
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == Size;
    }

    size_t size() const {
        return count;
    }

    void clear() {
        head = tail = count = 0;
    }

#ifdef ARDUINO
    void flush() {}
#endif
private:
    uint8_t buffer[Size];
    size_t head;
    size_t tail;
    size_t count;
};
