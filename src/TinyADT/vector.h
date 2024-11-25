#pragma once

#include <stdint.h>

template <class T>
class Vector {
public:
	class iterator {
	public:
		constexpr iterator() : pointer_(nullptr) {}
		constexpr iterator(const T* pointer) : pointer_(pointer) {}

		iterator& operator=(const iterator& rhs) {
			pointer_ = rhs.pointer_;
			return *this;
		}

		T& operator*() {
			return *pointer_;
		}

		bool operator==(const iterator& rhs) {
			return pointer_ == rhs.pointer_;
		}
		bool operator!=(const iterator& rhs) {
			return pointer_ != rhs.pointer_;
		}

		iterator& operator++() {
			pointer_ += 1;
			return *this;
		}
		iterator operator++(int) {
			iterator temp = *this;
			pointer_ += 1;
			return temp;
		}

		iterator& operator--() {
			pointer_ -= 1;
			return *this;
		}
		iterator operator--(int) {
			iterator temp = *this;
			pointer_ -= 1;
			return temp;
		}

		iterator& operator+=(const int rhs) {
			pointer_ += rhs;
			return *this;
		}
		iterator operator+(const int rhs) {
			iterator temp = *this;
			temp += rhs;
			return temp;
		}

		iterator& operator-=(const int rhs) {
			pointer_ -= rhs;
			return *this;
		}
		iterator operator-(const int rhs) {
			iterator temp = *this;
			temp -= rhs;
			return temp;
		}

	private:
		T* pointer_;
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
	virtual T& operator[](int index);
	// Append
	virtual bool insert(int index, const T &item);
	virtual bool push_back(const T &item);
	virtual T& emplace_back();
	// Remove
	virtual T pop_back();
};

template <class T, uint16_t Capacity>
class StaticVector : public Vector<T> {
public:
	StaticVector() {
		count_ = 0;
		data_[Capacity] = T();
	}

	uint16_t size() override {
		return count_;
	}

	uint16_t capacity() override {
		return Capacity;
	}

	T& at(int index) override {
		if (count_ <= 0 || index < 0 || index >= count_) {
			// Returns empty
			return data_[Capacity];
		}
		return data_[index];
	}

	T& operator[](int index) override {
		return data_[index];
	}

	bool insert(int index, const T &item) override {
		if (count_ >= Capacity) {
			return false;
		}
		if (index < count_) {
			for (int i = count_; i > index; i--) {
				data_[i] = data_[i - 1];
			}
		} else if (index > count_) {
			return false;
		}
		data_[index] = item;
		count_ += 1;
		return true;
	}

	bool push_back(const T &item) override {
		if (count_ >= Capacity) {
			return false;
		}
		data_[count_++] = item;
		return true;
	}

	T& emplace_back() override {
		return data_[count_++];
	}

	T pop_back() override {
		T result = data_[count_];
		count_ -= 1;
		data_[count_] = T();
		return result;
	}

	void clear() override {
		for (int i = 0; i < count_; i++) {
			data_[i] = T();
		}
		count_ = 0;
	}

	T* data() override {
		return data_;
	}

	typename Vector<T>::iterator begin() override {
		return typename Vector<T>::iterator(data_);
	}

	typename Vector<T>::iterator end() override {
		return typename Vector<T>::iterator(data_ + count_ - 1);
	}

private:
	T data_[Capacity];
	uint16_t count_ = 0;
};
