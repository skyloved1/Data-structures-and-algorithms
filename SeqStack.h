#pragma once
#ifndef SEQSTACK_H
#define SEQSTACK_H
#include "SqlList0.h"
#include <initializer_list>
#include "Basic_Iterator.h"

template<typename DataType>
class SeqStack
{
public:
	SeqStack() : stack(), topIndex(-1) {}
	SeqStack(int Size, DataType default_val = DataType()) : stack(Size, default_val), topIndex(Size - 1) {}
	SeqStack(SeqStack<DataType>& L) : stack(L.stack), topIndex(L.topIndex) {}
	SeqStack(SeqStack<DataType>&& L) noexcept;
	SeqStack(const DataType* arr, size_t Size) : stack(arr, Size), topIndex(Size - 1) {}
	SeqStack(const DataType* arr_first, const DataType* arr_last) : stack(arr_first, arr_last), topIndex(arr_last - arr_first - 1) {}
	SeqStack(std::initializer_list<DataType> list) : stack(list), topIndex(list.size() - 1) {}
	~SeqStack();

	// common methods
	bool push_back(const DataType& val) {
		stack.push_back(val);
		++topIndex;
		return true;
	}
	bool pop_back(DataType& other) {
		if (!empty()) {
			other = stack[topIndex];
			stack.pop_back();
			--topIndex;
			return true;
		}
		return false;
	}
	bool pop_back() {
		if (!empty()) {
			stack.pop_back();
			--topIndex;
			return true;
		}
		return false;
	}
	DataType get() {
		return stack[topIndex];
	}
	const DataType& get() const {
		return stack[topIndex];
	}
	bool copy_to_arr(DataType* _first, DataType* _last, DataType* _destination) const {
		return stack.copy_to_arr(_first, _last, _destination);
	}
	bool empty() const { return topIndex == -1; }
	bool full() const { return topIndex == stack.get_capacity() - 1; }

	// Iterator
	class Iterator : public BasicIterator<DataType>
	{
	public:
		Iterator(DataType* ptr = nullptr) : BasicIterator<DataType>(ptr) {}
	};

	Iterator begin();
	Iterator end();

private:
	SequenceList<DataType> stack;
	int topIndex;
};

template<typename DataType>
inline SeqStack<DataType>::SeqStack(SeqStack<DataType>&& L) noexcept
	: stack(std::move(L.stack)), topIndex(L.topIndex) {
	L.topIndex = -1;
}

template<typename DataType>
SeqStack<DataType>::~SeqStack() {}

template<typename DataType>
typename SeqStack<DataType>::Iterator SeqStack<DataType>::begin() {
	return Iterator(stack.begin());
}

template<typename DataType>
typename SeqStack<DataType>::Iterator SeqStack<DataType>::end() {
	return Iterator(stack.begin() + topIndex + 1);
}

#endif // !SEQSTACK_H