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
	virtual uint16_t size() = 0;
	virtual uint16_t capacity() = 0;
	virtual void clear() = 0;
	virtual T* data() = 0;
	// Iterators
	virtual iterator begin() = 0;
	virtual iterator end() = 0;
	// Accessors
	virtual T& at(int index) = 0;
	virtual T& at_end(int index) = 0;
	virtual T& operator[](int index) = 0;
	// Append
	virtual bool push_front(const T &item) = 0;
	virtual bool push_back(const T &item) = 0;
	virtual T& emplace_back() = 0;
	virtual T& emplace_front() = 0;
	// Remove
	virtual T& pop_front() = 0;
	virtual T& pop_back() = 0;

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

	T& at_end(int index) override {
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

	template <typename... RestT>
	bool push_front(const T &item, RestT... restItems) {
		this->push_front(item);
		return this->push_front(restItems...);
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

	template <typename... RestT>
	bool push_back(const T &item, RestT... restItems) {
		this->push_back(item);
		return this->push_back(restItems...);
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

protected:
    uint16_t front_, back_, count_;
    T data_[Capacity + 1];
};
