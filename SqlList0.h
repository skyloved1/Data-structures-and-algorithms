#pragma once
#ifndef SEQUENCELIST_H
#define SEQUENCELIST_H
#include <initializer_list>
#include <iostream>
template<typename DataType>
class SequenceList
{
public:
	//Iterator
	using Iterator = DataType*;
	using const_Iterator = const DataType*;
	//Iterator _begin;
	//Iterator _end;
	//constructor

	SequenceList();
	SequenceList(int Size, DataType default_val = 0);
	SequenceList(const SequenceList<DataType>& L);
	SequenceList(const DataType* arr, size_t Size);;
	SequenceList(const DataType* arr_first, const DataType* arr_last);
	SequenceList(std::initializer_list<DataType> list);
	~SequenceList();
	//method
	bool push_back(const DataType& val);
	bool pop_back();
	bool insert_node(const DataType& val, size_t pos);
	bool delete_node(size_t pos);
	bool erase(Iterator _first, Iterator _last);		//将区间内的数都设置为0
	bool delete_node(Iterator _first, Iterator _last);	//删除区间内的节点
	bool copy_to_arr(Iterator _first, Iterator _last, DataType* _destnation); //将区间内的内容 赋值给普通数组
	bool delete_first_val(DataType val);									//删除第一个值为val的元素
	bool delete_all_val(DataType val);										//删除所有值为Val的元素 O(n)
	Iterator begin() { return &_ptr[0]; }
	Iterator end() { return &_ptr[currentLength]; }
	//common bool
	bool  isEmpty() {
		return currentLength == 0;
	}
	bool isFull() {
		return currentLength == capacity;
	}

	//getter
	size_t get_length() {
		return currentLength;
	}
	// operator
	DataType operator[](size_t index) {
		if (index < currentLength)
		{
			return _ptr[index];
		}
		throw "超出当前长度，获取内容失败！\n";
	}
	friend  std::ostream& operator<<(std::ostream& os, const SequenceList& L);

	SequenceList<DataType>& operator=(const SequenceList<DataType>& L);
	//setter
	void resize(size_t size) {
		if (size > get_length())
		{
			new_capacity(size * 2 + 1);
		}
		if (size < get_length())
		{
			//消除列表中的节点
			size_t dx = currentLength - size;
			erase(end() - dx - 1, end());
			currentLength = size;
		}
	}
protected:
	size_t get_capacity() {
		return capacity;
	}

	void new_capacity(int size) {
		DataType* temp = new DataType[currentLength + 10];
		for (size_t i = 0; i < get_length(); i++)
		{
			temp[i] = _ptr[i];
		}
		_ptr = temp;
	}

private:
	size_t currentLength;
	size_t capacity;
	DataType* _ptr;
	enum CONSTANT { DEFAULT_SPACE = 16 };
};

template<typename DataType>
inline SequenceList<DataType>::SequenceList()
{
	_ptr = new DataType[CONSTANT::DEFAULT_SPACE];

	currentLength = CONSTANT::DEFAULT_SPACE;
	capacity = CONSTANT::DEFAULT_SPACE;
}

template<typename DataType>
inline SequenceList<DataType>::SequenceList(int Size, DataType default_val)
{
	capacity = Size * 2;
	_ptr = new DataType[capacity]{ default_val };
	currentLength = Size;
}

template<typename DataType>
inline SequenceList<DataType>::SequenceList(const SequenceList<DataType>& L)
{
	capacity = L.capacity;
	currentLength = L.currentLength;
	//delete[] _ptr;
	_ptr = new DataType[capacity + 1];
	for (size_t i = 0; i < L.currentLength; i++)
	{
		_ptr[i] = L._ptr[i];
	}
}

template<typename DataType>
inline SequenceList<DataType>::SequenceList(const DataType* arr, size_t Size)
{
	currentLength = Size;
	capacity = Size * 2;
	_ptr = new DataType[capacity]{ DataType() };
	for (size_t i = 0; i < Size; i++)
	{
		_ptr[i] = arr[i];
	}
}

template<typename DataType>
inline SequenceList<DataType>::SequenceList(const DataType* arr_first, const DataType* arr_last)
{
	size_t Size = (arr_last - arr_first);
	currentLength = Size;
	capacity = Size * 2;
	_ptr = new DataType[capacity]{ DataType() };
	int count = 0;
	while (arr_first < arr_last)
	{
		_ptr[count++] = *(arr_first++);
	}
}

template<typename DataType>
inline SequenceList<DataType>::SequenceList(std::initializer_list<DataType> list)
{
	currentLength = list.size();
	capacity = currentLength * 2;
	_ptr = new DataType[capacity]{ DataType() };
	int j = 0;
	for (auto i = list.begin(); i != list.end(); i++, j++)
	{
		_ptr[j] = *i;
	}
}

template<typename DataType>
inline SequenceList<DataType>::~SequenceList()
{
	delete[]_ptr;
}

template<typename DataType>
inline bool SequenceList<DataType>::push_back(const DataType& val)
{
	if (currentLength + 1 >= capacity)
	{
		resize(capacity);
	}
	_ptr[currentLength] = val;
	++currentLength;
	return _ptr[currentLength - 1] == val;
}

template<typename DataType>
inline bool SequenceList<DataType>::pop_back()
{
	if (!isEmpty())
	{
		_ptr[currentLength - 1] = DataType();

		--currentLength;
		return 1;
	}
	else
	{
		return 0;
	}
}

template<typename DataType>
inline bool SequenceList<DataType>::insert_node(const DataType& val, size_t pos)
{
	pos -= 1;
	if (pos > currentLength)
	{
		return false;
	}
	if (currentLength + 1 >= capacity)
	{
		resize(currentLength + 1);
	}

	for (size_t i = currentLength; i > pos; --i)
	{
		_ptr[i] = _ptr[i - 1];
	}
	_ptr[pos] = val;
	++currentLength;
	return 1;
}

template<typename DataType>
inline bool SequenceList<DataType>::delete_node(size_t pos)
{
	pos -= 1;
	if (pos >= currentLength)
	{
		return 0;
	}
	for (size_t i = pos; i < currentLength; ++i)
	{
		_ptr[i] = _ptr[i + 1];
	}
	--currentLength;
	return 1;
}

template<typename DataType>
inline bool SequenceList<DataType>::delete_node(Iterator _first, Iterator _last)
{
	if (_first < _last && _last <= this->end())
	{
		int Tmplength = _last - _first;
		for (auto i = _last; i != this->end(); ++i)
		{
			*(i - Tmplength) = *i;
		}
		currentLength -= Tmplength;
		return true;
	}
	return false;
}
template<typename DataType>
inline bool SequenceList<DataType>::copy_to_arr(Iterator _first, Iterator _last, DataType* _destnation)
{
	if (_first < _last)
	{
		int count = 0;
		while (_first < _last) {
			_destnation[count++] = *(_first++);
		}
		return 1;
	}
	return 0;
}
//复杂度为O(n)
template<typename DataType>
inline bool SequenceList<DataType>::delete_first_val(DataType val)
{
	bool haveFound = false;
	size_t i = 0;
	for (; i < this->get_length(); i++)
	{
		if (_ptr[i] == val)
		{
			haveFound = true;
			break;
		}
	}
	if (haveFound)
	{
		delete_node(i + 1);
		return true;
	}

	return false;
}
//复杂度为O(n)
template<typename DataType>
inline bool SequenceList<DataType>::delete_all_val(DataType val)
{	//双指针
	Iterator i = this->begin();
	Iterator j = this->begin();
	for (; j < this->end(); ++j)
	{
		if ((j + 1) != (this->end())) {//快指针没有到表尾
			if (*j == val)//如果快指针指向的是要删除的值
			{
				++j;		//越过这个值，把快指针的下一个值赋值给	慢指针  （无法解决最后一个元素）
			}
			*i = *j;		//赋值

			if (*i != val)	//判断如果快指针的下一个值仍是要删除的值，会赋值给 慢指针，所以要判定慢指针是否为要删除的值
			{				//如果是要删除的值，则慢指针不移动
				++i;		//如果不是要删除的值，才会移动
			}
		}
		else
		{
			break;
		}
	}
	currentLength = i - this->begin() + 1;		//极端情况：慢指针指向的是要删除的值，快指针指向最后一个元素时也是要删除的值
	if (_ptr[currentLength - 1] == val)			//只能特化处理
	{
		pop_back();
	}

	return 1;
}

template<typename DataType>
inline SequenceList<DataType>& SequenceList<DataType>::operator=(const SequenceList<DataType>& L)
{
	for (size_t i = 0; i < L.currentLength; i++)
	{
		this[i] = L[i];
	}
	return this;
}

template<typename Datatype>
std::ostream& operator<<(std::ostream& os, SequenceList<Datatype>& L)
{
	for (int i = 0; i < L.get_length(); i++)
	{
		os << L[i] << '\t';
	}
	os << std::endl;
	return os;
}
template<typename DataType>
inline bool SequenceList<DataType>::erase(Iterator _first, Iterator _last)
{
	if (_first < _last)
	{
		for (auto it = _first; it != _last; ++it)
		{
			*it = DataType(); // 将区间内的数都设置为0
		}
		return true;
	}
	return false;
}
#endif // !SEQUENCELIST_H