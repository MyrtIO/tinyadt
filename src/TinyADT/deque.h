#pragma once

#include <stdint.h>

// Deque is a double ended queue.
template <class T>
class Deque {
public:
	virtual uint16_t size();
	virtual uint16_t capacity();
	virtual T* begin();
	virtual T* end();
	virtual T& at(int index);
	virtual T& operator[](int index);
	virtual bool push_front(const T &item);
	virtual bool push_back(const T &item);
	virtual T& pop_front();
	virtual T& pop_back();
	virtual T& emplace_back();
	virtual T& emplace_front();
	virtual void clear();
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

    T* begin() override {
		if (count_ == 0) {
			return nullptr;
		}
		return &data_[front_];
	}

    T* end() override {
		if (count_ == 0) {
			return nullptr;
		}
		return &data_[back_ - 1];
	}

	T& at(int index) override {
		if (count_ <= 0 || index < 0 || index >= count_) {
			// Returns empty
			return data_[Capacity];
		}
		return data_[(front_ + index) % Capacity];
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

private:
    uint16_t front_, back_, count_;
    T data_[Capacity + 1];
};
