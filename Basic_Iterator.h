#pragma once
#ifndef BASIC_ITERATOR_H
#define BASIC_ITERATOR_H

#include <iterator>

template<typename T>
class BasicIterator
{
public:
	// 构造函数
	BasicIterator() :ptr(nullptr) {};
	BasicIterator(T* ptr = nullptr) : ptr(ptr) {}

	// 虚析构函数
	virtual ~BasicIterator() {}

	// 解引用操作符
	virtual T& operator*() const { return *ptr; }

	// 指针访问操作符
	virtual T* operator->() const { return ptr; }

	// 前置递增操作符
	virtual  BasicIterator& operator++() {
		++ptr;
		return *this;
	}

	// 后置递增操作符
	virtual  BasicIterator operator++(int) {
		BasicIterator temp = *this;
		++(*this);
		return temp;
	}
	virtual  BasicIterator& operator=(const BasicIterator& other) {
		if (this->ptr != other.ptr)
		{
			this->ptr = other.ptr;
		}
		return *this;
	}

	// 相等比较操作符
	virtual bool operator==(const BasicIterator& other) const {
		return ptr == other.ptr;
	}

	// 不相等比较操作符
	virtual bool operator!=(const BasicIterator& other) const {
		return ptr != other.ptr;
	}

	// 小于比较操作符
	virtual bool operator<(const BasicIterator& other) const {
		return ptr < other.ptr;
	}

	// 小于等于比较操作符
	virtual bool operator<=(const BasicIterator& other) const {
		return ptr <= other.ptr;
	}

	// 大于比较操作符
	virtual bool operator>(const BasicIterator& other) const {
		return ptr > other.ptr;
	}

	// 大于等于比较操作符
	virtual bool operator>=(const BasicIterator& other) const {
		return ptr >= other.ptr;
	}

	// 返回常量引用随机访问符
	virtual const T& operator[](size_t index) const {
		return ptr[index];
	}

	// 返回临时变量引用随机访问符
	virtual T operator[](size_t index) {
		return ptr[index];
	}

private:
	T* ptr;
};

#endif // BASIC_ITERATOR_H
