#pragma once
#ifndef DOUBLE_SINGLELINKED_H
#define DOUBLE_SINGLELINKED_H
#include <initializer_list>
#include <utility> // for std::move
#include "Basic_Iterator.h"
template<typename DataType>
class Double_LinkedList
{
public:
	Double_LinkedList();
	Double_LinkedList(size_t length, DataType default_val = DataType());
	Double_LinkedList(const Double_LinkedList<DataType>& other);
	Double_LinkedList(Double_LinkedList<DataType>&& other) noexcept;
	Double_LinkedList(DataType* _first, DataType* _end);
	Double_LinkedList(std::initializer_list<DataType> init_list);

	~Double_LinkedList();

	Double_LinkedList<DataType>& operator=(const Double_LinkedList<DataType>& other);
	Double_LinkedList<DataType>& operator=(Double_LinkedList<DataType>&& other) noexcept;
	//common method

	//头插法
	bool head_insert(const DataType& val);
	//尾插法
	bool tail_insert(const DataType& val);
	//设置链表是否循环(默认为否)
	bool set_loop(bool b = false);
	bool insertNode(const DataType& val);
	bool deleteNode(size_t index);
	//查找值，_start 和_end代表要查找的范围
	template<typename bool_Callable, typename...Args>
	const DataType& select_val(bool_Callable _callable, Args...args, Double_LinkedList<DataType>* _start = head->Next, Double_LinkedList<DataType>* _end = tail);

	bool push_back(const DataType& val);
	bool push_front(const DataType* val) { return head_insert(val) };
	bool pop_back();
	bool pop_front();
	//getter

	bool isLoop()const;
	bool isEmpty()const;
	size_t getLength()const;

	class Iterator
	{
	public:
		Iterator(Double_LinkedList<DataType>* ptr = nullptr) : node(ptr) {}

		DataType& operator*() const { return node->data; }
		DataType* operator->() const { return &(node->data); }

		// 前置++
		Iterator& operator++() {
			node = node->Next;
			return *this;
		}

		// 后置++
		Iterator operator++(int) {
			Iterator temp = *this;
			node = node->Next;
			return temp;
		}

		// 前置--
		Iterator& operator--() {
			node = node->Previous;
			return *this;
		}

		// 后置--
		Iterator operator--(int) {
			Iterator temp = *this;
			node = node->Previous;
			return temp;
		}
		bool operator==(const Iterator& other) const { return node == other.node; }
		bool operator!=(const Iterator& other) const { return node != other.node; }

	private:
		Double_LinkedList<DataType>* node;
	};

	Iterator begin() { return Iterator(head); }
	Iterator end() { return Iterator(nullptr); }

	// 其他方法和成员变量...

//Operator

// 重载随机访问运算符
	DataType& operator[](size_t index);
	const DataType& operator[](size_t index) const;

private:
	DataType data;
	size_t length;
	Double_LinkedList<DataType>* Previous;
	Double_LinkedList<DataType>* Next;
	Double_LinkedList<DataType>* head;
	Double_LinkedList<DataType>* tail;
};

template<typename DataType>
Double_LinkedList<DataType>::Double_LinkedList() : length(0), head(nullptr), tail(nullptr), Previous(nullptr), Next(nullptr) {}

template<typename DataType>
Double_LinkedList<DataType>::Double_LinkedList(size_t length, DataType default_val) : length(length), head(nullptr), tail(nullptr), Previous(nullptr), Next(nullptr) {
	for (size_t i = 0; i < length; ++i) {
		tail_insert(default_val);
	}
}

template<typename DataType>
Double_LinkedList<DataType>::Double_LinkedList(const Double_LinkedList<DataType>& other) : length(0), head(nullptr), tail(nullptr), Previous(nullptr), Next(nullptr) {
	Double_LinkedList<DataType>* current = other.head;
	while (current) {
		tail_insert(current->data);
		current = current->Next;
	}
}

template<typename DataType>
Double_LinkedList<DataType>::Double_LinkedList(Double_LinkedList<DataType>&& other) noexcept : length(other.length), head(other.head), tail(other.tail), Previous(other.Previous), Next(other.Next) {
	other.length = 0;
	other.head = nullptr;
	other.tail = nullptr;
	other.Previous = nullptr;
	other.Next = nullptr;
}

template<typename DataType>
Double_LinkedList<DataType>::Double_LinkedList(DataType* _first, DataType* _last) : length(0), head(nullptr), tail(nullptr), Previous(nullptr), Next(nullptr) {
	while (_first != _last) {
		tail_insert(*_first);
		++_first;
	}
}

template<typename DataType>
Double_LinkedList<DataType>::Double_LinkedList(std::initializer_list<DataType> init_list) : length(0), head(nullptr), tail(nullptr), Previous(nullptr), Next(nullptr) {
	for (const auto& val : init_list) {
		tail_insert(val);
	}
}

template<typename DataType>
Double_LinkedList<DataType>::~Double_LinkedList() {
	while (head) {
		Double_LinkedList<DataType>* temp = head;
		head = head->Next;
		delete temp;
	}
}

template<typename DataType>
Double_LinkedList<DataType>& Double_LinkedList<DataType>::operator=(const Double_LinkedList<DataType>& other) {
	if (this != &other) {
		Double_LinkedList<DataType> temp(other);
		std::swap(length, temp.length);
		std::swap(head, temp.head);
		std::swap(tail, temp.tail);
		std::swap(Previous, temp.Previous);
		std::swap(Next, temp.Next);
	}
	return *this;
}

template<typename DataType>
Double_LinkedList<DataType>& Double_LinkedList<DataType>::operator=(Double_LinkedList<DataType>&& other) noexcept {
	if (this != &other) {
		length = other.length;
		head = other.head;
		tail = other.tail;
		Previous = other.Previous;
		Next = other.Next;

		other.length = 0;
		other.head = nullptr;
		other.tail = nullptr;
		other.Previous = nullptr;
		other.Next = nullptr;
	}
	return *this;
}

template<typename DataType>
bool Double_LinkedList<DataType>::head_insert(const DataType& val) {
	Double_LinkedList<DataType>* newNode = new Double_LinkedList<DataType>();
	newNode->data = val;
	newNode->Next = head;
	if (head) {
		head->Previous = newNode;
	}
	head = newNode;
	if (!tail) {
		tail = newNode;
	}
	++length;
	return true;
}

template<typename DataType>
bool Double_LinkedList<DataType>::tail_insert(const DataType& val) {
	Double_LinkedList<DataType>* newNode = new Double_LinkedList<DataType>();
	newNode->data = val;
	newNode->Previous = tail;
	if (tail) {
		tail->Next = newNode;
	}
	tail = newNode;
	if (!head) {
		head = newNode;
	}
	++length;
	return true;
}

template<typename DataType>
bool Double_LinkedList<DataType>::set_loop(bool b) {
	if (b) {
		if (tail) {
			tail->Next = head;
			if (head) {
				head->Previous = tail;
			}
		}
	}
	else {
		if (tail) {
			tail->Next = nullptr;
		}
		if (head) {
			head->Previous = nullptr;
		}
	}
	return true;
}

template<typename DataType>
bool Double_LinkedList<DataType>::insertNode(const DataType& val) {
	return tail_insert(val);
}

template<typename DataType>
inline bool Double_LinkedList<DataType>::deleteNode(size_t index)
{
	if (index >= length) {
		return false;
	}

	if (index == 0) {
		pop_front();
		return true;
	}

	Double_LinkedList<DataType>* current = head;
	for (size_t i = 0; i < index - 1; ++i) {
		current = current->Next;
	}

	Double_LinkedList<DataType>* nodeToDelete = current->Next;
	current->Next = nodeToDelete->Next;
	if (current->Next) {
		current->Next->Previous = current;
	}

	if (nodeToDelete == tail) {
		tail = current;
	}

	delete nodeToDelete;
	--length;

	return true;
}

template<typename DataType>
inline bool Double_LinkedList<DataType>::push_back(const DataType& val)
{
	Double_LinkedList<DataType>* temp = new Double_LinkedList();
	if (temp)
	{
		temp->data = val;
		temp->Previous = tail;
		tail->Next = temp;
		return true;
	}
	return false;
}

template<typename DataType>
inline bool Double_LinkedList<DataType>::pop_back()
{
	Double_LinkedList<DataType>* temp = tail;
	tail = temp->Previous;
	tail->Next = nullptr;
	delete temp;
	return true;
}

// The code you provided has a syntax error. There is a typo in the pop_front() method implementation. The assignment operator (=>) should be replaced with the dereference operator (->) to access the Previous pointer of the head node. Here's the corrected code:

template<typename DataType>
inline bool Double_LinkedList<DataType>::pop_front()
{
	Double_LinkedList<DataType>* temp = head;
	head = head->Next;
	head->Previous = nullptr;
	delete temp;
	return true;
}

template<typename DataType>
template<typename bool_Callable, typename...Args>
const DataType& Double_LinkedList<DataType>::select_val(bool_Callable _callable, Args...args, Double_LinkedList<DataType>* _start, Double_LinkedList<DataType>* _end) {
	Double_LinkedList<DataType>* current = _start;
	while (current != _end) {
		if (_callable(current->data, args...)) {
			return current->data;
		}
		current = current->Next;
	}
	throw std::runtime_error("Value not found");
}

template<typename DataType>
bool Double_LinkedList<DataType>::isLoop() const {
	return tail && tail->Next == head;
}

template<typename DataType>
bool Double_LinkedList<DataType>::isEmpty() const {
	return length == 0;
}

template<typename DataType>
size_t Double_LinkedList<DataType>::getLength() const {
	return length;
}
template<typename DataType>
DataType& Double_LinkedList<DataType>::operator[](size_t index) {
	if (index >= length) {
		throw std::out_of_range("Index out of range");
	}
	Double_LinkedList<DataType>* current = head;
	for (size_t i = 0; i < index; ++i) {
		current = current->Next;
	}
	return current->data;
}

template<typename DataType>
const DataType& Double_LinkedList<DataType>::operator[](size_t index) const {
	if (index >= length) {
		throw std::out_of_range("Index out of range");
	}
	Double_LinkedList<DataType>* current = head;
	for (size_t i = 0; i < index; ++i) {
		current = current->Next;
	}
	return current->data;
}

#endif // !DOUBLE_SINGLELINKED_H
