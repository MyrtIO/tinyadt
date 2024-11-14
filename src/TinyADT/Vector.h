#pragma once

#include <stdint.h>

#ifndef ARDUINO
#include <string.h>
#endif

template <typename T>
class Vector {
public:
	Vector() :
		data_(nullptr),
		size_(0),
		capacity_(0) {}
	~Vector() {
		if (data_ != nullptr) {
			delete[] data_;
		}
	}

	bool insert(const T& item) {
        size_t idx = size_ + 1;
		if (idx >= capacity_) {
			if (capacity_ == 0) {
				resize_(8);
			} else {
				resize_(capacity_ * 2);
			}
		}
		data_[size_] = item;
		size_ = idx;
		return true;
	}

	void reserve(uint16_t capacity) {
		if (capacity > capacity_) {
			resize_(capacity);
		}
	}

	T& pop() {
		T ret = data_[size_ - 1];
		data_[size_ - 1] = T();
		size_ -= 1;
		return ret;
	}

    size_t size() const {
        return size_;
    }

	size_t capacity() const {
		return capacity_;
	}

    T& operator [](int idx) {
        return data_[idx];
    }

	void trim() {
		resize_(size_);
	}

private:
	T* data_;
	size_t size_;
	size_t capacity_;

	void resize_(size_t capacity) {
		T* newData = new T[capacity];
		if (data_ != nullptr) {
			memmove(newData, data_, size_ * sizeof(T));
			delete[] data_;
		}
		capacity_ = capacity;
		data_ = newData;
	}
};
