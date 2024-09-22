#pragma once
#ifndef MYVECTOR_H
#define MYVECTOR_H
template<typename T>
class Vector {
public:
	explicit Vector(int initSize = 0)
		:theSize(initSize), theCapacity(initSize + CONSTANT::SPACE_CAPACITY) {
		T_ptr = new T[theCapacity]{ 0 };
	}
	Vector(const Vector& rhs) :T_ptr(nullptr) {
		*this = rhs;
	}
	~Vector() { delete[] T_ptr; }

	const Vector& operator=(const Vector& rhs) {
		if (this != &rhs) {
			delete[] T_ptr;
			theSize = rhs.theSize;
			theCapacity = rhs.theCapacity;

			T_ptr = new T[capacity()];
			for (size_t k = 0; k < size(); k++)
			{
				T_ptr[k] = rhs.T_ptr[k];
			}
		}
		return *this;
	}
	void resize(int newSize) {
		if (newSize > theCapacity) {
			reserve(newSize * 2 + 1);
			theSize = newSize;
		}
	}
	void reserve(int newCapacity) {
		if (newCapacity < theSize) {
			return;
		}
		T* oldArray = T_ptr;
		T_ptr = new T[newCapacity];
		for (size_t i = 0; i < theSize; i++)
		{
			T_ptr[i] = oldArray[i];
		}
		theCapacity = newCapacity;
		delete[]oldArray;
	}
	T& operator[](int index) { return T_ptr[index]; }
	const T& operator[](int index)const { return T_ptr[index]; }

	bool  isEmpty()const {
		return (size() == 0);
	}
	int size()const {
		return theSize;
	}
	int capacity()const { return theCapacity; }

	void push_back(const T& x) {
		if (theSize == theCapacity)
		{
			throw "Capacity has full! Try use reserve to change capacity";
		}
		T_ptr[theSize++] = x;
	}
	void pop_back() {
		T_ptr[theSize - 1] = 0;
		--theSize;
	}
	const T& back() const {
		return T_ptr[theSize - 1];
	}

	using iterator = T*;
	using const_iterator = const T*;
	iterator begin() {
		return &T_ptr[0];
	}
	iterator end() {
		return&T_ptr[theSize];
	}
	const_iterator begin()const {
		return &T_ptr[0];
	}
	const_iterator end()const {
		return &T_ptr[theSize];
	}

private:
	int theSize;
	int theCapacity;
	T* T_ptr;
	enum CONSTANT { SPACE_CAPACITY = 16 };
};

#endif // !MYVECTOR_H
