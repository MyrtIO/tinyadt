#pragma once

template <class T>
class IVector {
public:
	virtual bool insert(T value);
	virtual T& operator [](int idx);
	virtual T& at(int idx);
	virtual int size() const = 0;

	virtual ~IVector() = default;
};
