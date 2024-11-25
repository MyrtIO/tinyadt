#pragma once

#include <stdint.h>
#include "iterator.h"

// Deque is a double ended queue.
template <class T>
class Deque {
public:
	class iterator {
	public:
		iterator() : deque_(nullptr), offset_(0) {}
		iterator(Deque<T>* deque, int offset = 0) : deque_(deque), offset_(offset) {}

		iterator& operator=(const iterator& rhs) {
			offset_ = rhs.offset_;
			deque_ = rhs.deque_;
			return *this;
		}

		iterator& operator=(const int rhs) {
			offset_ = rhs;
			return *this;
		}


		T& operator*() {
			return deque_->at(offset_);
		}

		bool operator==(const iterator& rhs) {
			return offset_ == rhs.offset_ && deque_ == rhs.deque_;
		}
		bool operator!=(const iterator& rhs) {
			return offset_ != rhs.offset_ || deque_ != rhs.deque_;
		}

		iterator& operator++() {
			offset_ += 1;
			return *this;
		}
		iterator operator++(int) {
			iterator temp = *this;
			offset_ += 1;
			return temp;
		}

		iterator& operator--() {
			offset_ -= 1;
			return *this;
		}
		iterator operator--(int) {
			iterator temp = *this;
			offset_ -= 1;
			return temp;
		}

		iterator& operator+=(const int rhs) {
			offset_ += rhs;
			return *this;
		}
		iterator operator+(const int rhs) {
			iterator temp = *this;
			temp += rhs;
			return temp;
		}

		iterator& operator-=(const int rhs) {
			offset_ -= rhs;
			return *this;
		}
		iterator operator-(const int rhs) {
			iterator temp = *this;
			temp -= rhs;
			return temp;
		}

	private:
		int offset_ = 0;
		Deque<T>* deque_;
	};

	// Storage
	virtual uint16_t size();
	virtual uint16_t capacity();
	virtual void clear();
	virtual T* data();
	// Iterators
	virtual iterator begin();
	virtual iterator end();
	// Accessors
	virtual T& at(int index);
	virtual T& at_end(int index);
	virtual T& operator[](int index);
	// Append
	virtual bool push_front(const T &item);
	virtual bool push_back(const T &item);
	virtual T& emplace_back();
	virtual T& emplace_front();
	// Remove
	virtual T& pop_front();
	virtual T& pop_back();

};

// StaticDeque is a double ended queue with a fixed capacity.
template<class T, uint16_t Capacity>
class StaticDeque: public Deque<T> {
public:
    StaticDeque() {
		front_ = 0;
		back_ = 0;
		count_ = 0;

		data_[Capacity] = T();
    }

    uint16_t size() override {
		return count_;
	}

	uint16_t capacity() override {
		return Capacity;
	}

    typename Deque<T>::iterator begin() override {
		return typename Deque<T>::iterator(this, 0);
	}

	typename Deque<T>::iterator end() override {
		return typename Deque<T>::iterator(this, count_ - 1);
	}

	T& at(int index) override {
		if (count_ <= 0 || index < 0 || index >= count_) {
			// Returns empty
			return data_[Capacity];
		}
		return data_[(front_ + index) % Capacity];
	}

	T& at_end(int index) {
		if (count_ <= 0 || index < 0 || index >= count_) {
			// Returns empty
			return data_[Capacity];
		}
		return data_[(back_ + index) % Capacity];
	}

	T& operator[](int index) override {
		return this->at(index);
	}

    bool push_front(const T &item) override {
		if (count_ >= Capacity) {
			return false;
		}
		if (count_ > 0) {
			if (front_ == 0) {
				front_ = Capacity - 1;
			} else {
				front_ -= 1;
			}
		}
		data_[front_] = item;
		count_ += 1;

		return true;
	}

    bool push_back(const T &item) override {
		if (count_ >= Capacity) {
			return false;
		}
		if (count_ > 0) {
			if (back_ == Capacity - 1) {
				back_ = 0;
			} else {
				back_ += 1;
			}
		}
		data_[back_] = item;
		count_ += 1;

		return true;
	}

	T& emplace_back() override {
		if (count_ >= Capacity) {
			return data_[Capacity];
		}
		if (back_ >= Capacity - 1) {
			back_ = 0;
		} else {
			back_ += 1;
		}
		count_ += 1;
		data_[back_] = T();
		return data_[back_];
	}

	T& emplace_front() override {
		if (count_ >= Capacity) {
			return data_[Capacity];
		}
		if (front_ == 0) {
			front_ = Capacity - 1;
		} else {
			front_ -= 1;
		}
		count_ += 1;
		data_[front_] = T();
		return data_[front_];
	}

	T& pop_front() override {
		if (count_ <= 0) {
			return data_[Capacity];
		}
		T& item = data_[front_];
		if (front_ == Capacity - 1) {
			front_ = 0;
		} else {
			front_ += 1;
		}
		count_ -= 1;

		return item;
	}

	T& pop_back() override {
		if (count_ <= 0) {
			return data_[Capacity];
		}
		T& item = data_[back_];
		if (back_ == 0) {
			back_ = Capacity - 1;
		} else {
			back_ -= 1;
		}
		count_ -= 1;

		return item;
	}

    void clear() override {
		front_ = back_ = count_ = 0;
	}

	T* data() override {
		return data_;
	}

private:
    uint16_t front_, back_, count_;
    T data_[Capacity + 1];
};
