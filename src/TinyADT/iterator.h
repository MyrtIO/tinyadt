#pragma once

template <class T>
class Iterator {
public:
	virtual Iterator& operator++();
	virtual Iterator& operator++(int);

	virtual Iterator& operator--();
	virtual Iterator& operator--(int);

	virtual T& operator*();
};

template <class T>
class RandomAccessIterator : public Iterator<T> {
public:
	virtual RandomAccessIterator& operator=(const int other);

	virtual RandomAccessIterator& operator+=(const int rhs);
	virtual RandomAccessIterator operator+(const int rhs);

	virtual RandomAccessIterator& operator-=(const int rhs);
	virtual RandomAccessIterator operator-(const int rhs);

};
