#pragma once

#include <stdint.h>

template <class T>
class Vector {
public:
	class iterator {
	public:
		constexpr iterator() : pointer_(nullptr) {}
		constexpr iterator(T* pointer) : pointer_(pointer) {}

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
	virtual uint16_t size() = 0;
	virtual uint16_t capacity() = 0;
	virtual void clear() = 0;
	virtual T* data() = 0;
	// Iterators
	virtual iterator begin() = 0;
	virtual iterator end() = 0;
	// Accessors
	virtual T& at(int index) = 0;
	virtual T& operator[](int index) = 0;
	// Append
	virtual bool insert(int index, const T &item) = 0;
	virtual bool push_back(const T &item) = 0;
	virtual T& emplace_back() = 0;
	// Remove
	virtual T pop_back() = 0;
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
		if (count_ <= 0 || index < 0 || (unsigned)index >= count_) {
			// Returns empty
			return data_[Capacity];
		}
		return data_[index];
	}

	T& operator[](int index) override {
		return data_[index];
	}

	bool insert(int index, const T &item) override {
		if (count_ >= Capacity || index < 0 || (unsigned)index > count_) {
			return false;
		}
		if ((unsigned)index < count_) {
			for (int i = count_; i > index; i--) {
				data_[i] = data_[i - 1];
			}
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

	template <typename... RestT>
	bool push_back(const T &item, RestT... restItems) {
		this->push_back(item);
		return this->push_back(restItems...);
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
		for (uint16_t i = 0; i < count_; i++) {
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

protected:
	T data_[Capacity + 1];
	uint16_t count_ = 0;
};
