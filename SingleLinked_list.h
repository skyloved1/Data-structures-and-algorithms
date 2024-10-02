#pragma once
#ifndef SINGLE_LINKED_LIST
#include <initializer_list>
#include <iostream>
//pos指的是按位，即第几个
template<typename DataType>
class SingleLinked_list_with_head
{
	class Iterator;// 前向声明
private:
	struct Node
	{
		DataType data;
		Node* Next;
		friend std::ostream& operator <<(std::ostream& os, const Node& node);
	};
	size_t length;
	Iterator head, last;
	Node* arr[];
public:
	class Iterator {
	public:
		Iterator();
		Iterator(Node* node);
		~Iterator();
		Node* operator++();
		Node* operator++(int);
		Node* operator=(Iterator& it);
		Node* operator=(Node* it);
		Node* get()const;
	private:
		Node* node;
	};
	SingleLinked_list_with_head();
	SingleLinked_list_with_head(size_t length, const  DataType& val);				//初始化长度为n的链表，其值为val
	SingleLinked_list_with_head(std::initializer_list list);				//支持初始化列表
	SingleLinked_list_with_head(DataType* _first, DataType* _last);			//把数组变为链表
	SingleLinked_list_with_head(const SingleLinked_list_with_head<DataType>& L);  //复制构造函数
	SingleLinked_list_with_head(SingleLinked_list_with_head<DataType>&& L); //移动构造函数
	~SingleLinked_list_with_head();

	//TODO 头插法 尾插法
	bool head_insert(size_t pos, DataType val);
	bool tail_insert(size_t pos, DataType val);
	//TODO  删除第一个值为val的删除所有值为val的，
	bool delete_first_val(DataType val);
	bool delete_all_val(DataType val);
	//TODO  插入前有序，插入后有序  默认升序
	bool insert_still_sequence_by_asc();
	//TODO 逆置单链表
	void reverse_list();
	template<typename Fn>
	size_t select_val(Fn Function, Iterator _first, Iterator _last);		//按值查找

	//common method
	bool delete_node(size_t pos);
	bool delete_node(Iterator _first, Iterator _last);
	Node& get_node(size_t pos) const;										//按位查找
	bool push_back(const DataType& val);
	bool push_front(const DataType& val);
	DataType pop_back();
	DataType pop_front();

	bool isEmpty() const;
	void copy_to_arr(Iterator _first, Iterator _lase);
	size_t getLength()const;
	Iterator getHead()const;
	Iterator getEnd()const;

	//operator
	friend std::ostream& operator <<(std::ostream& os, const SingleLinked_list_with_head& L);
	friend std::istream& operator >>(std::istream& is, Node* node);
	friend Node& operator[](size_t index);
};

#endif // !SINGLE_LINKED_LIST
