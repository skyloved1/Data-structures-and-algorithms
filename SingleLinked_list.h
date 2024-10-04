#pragma once
#ifndef SINGLE_LINKED_LIST
#include <initializer_list>
#include <iostream>
//pos指的是按位，即第几个
//单链表带头节点的实现
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
	//Node* index_arr[];
public:
	//内嵌类迭代器支持
	class Iterator {
	public:
		Iterator();
		Iterator(const Iterator& it);
		Iterator(Node* node);
		~Iterator();
		Node* operator++();
		Node* operator++(int);
		Node* operator=(Iterator& it)	const;
		bool operator!=(Iterator& it)	const;
		bool operator<(Iterator& it)	const;
		bool operator<=(Iterator& it)	const;
		bool operator>(Iterator& it)	const;
		bool operator>=(Iterator& it)	const;
		Node* operator=(Node* it)		const;
		bool operator!=(Node* it)		const;
		bool operator<(Node* it)		const;
		bool operator<=(Node* it)		const;
		bool operator>(Node* it)		const;
		bool operator>=(Node* it)		const;

		Node* get()const { return node_ptr };
		void set(Node* node);
		Node* node_ptr;
	};
	//默认构造函数 仅初始化头节点
	SingleLinked_list_with_head();
	//初始化长度为n的链表，其值为val
	SingleLinked_list_with_head(size_t length, const  DataType& val = DataType());
	//支持初始化列表
	SingleLinked_list_with_head(std::initializer_list list);
	//把数组变为链表
	SingleLinked_list_with_head(DataType* _first, DataType* _last);
	//复制构造函数
	SingleLinked_list_with_head(const SingleLinked_list_with_head<DataType>& L);
	//移动构造函数
	SingleLinked_list_with_head(SingleLinked_list_with_head<DataType>&& L);
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
//node结构体实现如下：

template<typename DataType>
std::ostream& operator<<(std::ostream& os, const typename SingleLinked_list_with_head<DataType>::Node& node)
{
	os << node.data;
	return os;
}

//内嵌类迭代器的实现如下:

template<typename DataType>
inline SingleLinked_list_with_head<DataType>::Iterator::Iterator()
{
	node_ptr = nullptr;
}

template<typename DataType>
inline SingleLinked_list_with_head<DataType>::Iterator::Iterator(const Iterator& it)
{
	if (it.node_ptr) {
		this->node_ptr = new Node(*it.node_ptr);
	}
	else {
		this->node_ptr = nullptr;
	}
}

template<typename DataType>
inline SingleLinked_list_with_head<DataType>::Iterator::Iterator(Node* node)
{
	node_ptr = new Node;
	node_ptr->data = node->data;
	node_ptr->Next = node->Next;
}

template<typename DataType>
inline SingleLinked_list_with_head<DataType>::Iterator::~Iterator()
{
	std::cout << "\n" << "该迭代器类已销毁" << std::endl;
	delete this->node_ptr;
}

template<typename DataType>
inline typename SingleLinked_list_with_head<DataType>::Node* SingleLinked_list_with_head<DataType>::Iterator::operator++()
{
	node_ptr = node_ptr->Next;
	return node_ptr;
}

template<typename DataType>
inline typename SingleLinked_list_with_head<DataType>::Node* SingleLinked_list_with_head<DataType>::Iterator::operator++(int)
{
	auto temp_ptr = this->node_ptr;
	node_ptr = node_ptr->Next;
	return temp_ptr;
}

template<typename DataType>
inline typename SingleLinked_list_with_head<DataType>::Node* SingleLinked_list_with_head<DataType>::Iterator::operator=(Iterator& it) const
{
	//采用深复制
	//if (this != &it) { // 防止自我赋值
	//	if (this->node_ptr) {
	//		delete this->node_ptr; // 删除当前节点，防止内存泄漏
	//	}
	//	if (it.node_ptr) { // 检查 it.node_ptr 是否为空
	//		this->node_ptr = new Node;
	//		this->node_ptr->data = it.node_ptr->data;
	//		// 深复制下一个节点
	//		if (it.node_ptr->Next) {
	//			this->node_ptr->Next = new Node;
	//			this->node_ptr->Next->data = it.node_ptr->data;
	//			this->node_ptr->Next->Next = it.node_ptr->Next;
	//		}
	//		else {
	//			this->node_ptr->Next = nullptr;
	//		}
	//	}
	//	else {
	//		this->node_ptr = nullptr;
	//	}
	//}

	//采用浅复制
	if (this->node_ptr != it.node_ptr)
	{
		this->node_ptr = it.node_ptr;
	}

	return this->node_ptr;
}

template<typename DataType>
inline bool SingleLinked_list_with_head<DataType>::Iterator::operator!=(Iterator& it) const
{
	return this->node_ptr != it.node_ptr;
}

template<typename DataType>
inline  bool SingleLinked_list_with_head<DataType>::Iterator::operator<(Iterator& it) const
{
	return this->node_ptr < it.node_ptr;
}

template<typename DataType>
inline  bool SingleLinked_list_with_head<DataType>::Iterator::operator<=(Iterator& it) const
{
	return this->node_ptr <= it.node_ptr;
}

template<typename DataType>
inline bool SingleLinked_list_with_head<DataType>::Iterator::operator>(Iterator& it) const
{
	return this->node_ptr > it.node_ptr;
}

template<typename DataType>
inline bool SingleLinked_list_with_head<DataType>::Iterator::operator>=(Iterator& it) const
{
	return this->node_ptr >= it.node_ptr;
}

template<typename DataType>
inline typename SingleLinked_list_with_head<DataType>::Node* SingleLinked_list_with_head<DataType>::Iterator::operator=(Node* it) const
{	//深复制
	//if (this->node_ptr != it)
	//{
	//	if (this->node_ptr) {
	//		delete this->node_ptr;
	//	}
	//	if (it) {
	//		this->node_ptr = new Node;
	//		this->node_ptr->data = it->data;
	//		// 深复制下一个节点
	//		if (it->Next) {
	//			this->node_ptr->Next = new Node;
	//			this->node_ptr->Next->data = it->Next->data;
	//			this->node_ptr->Next->Next = it->Next->Next;
	//		}
	//		else {
	//			this->node_ptr->Next = nullptr;
	//		}
	//	}
	//	else {
	//		this->node_ptr = nullptr;
	//	}
	//}

	//浅复制
	if (node_ptr != it)
	{
		this->node_ptr = it;
	}

	return this->node_ptr;
}

template<typename DataType>
inline bool SingleLinked_list_with_head<DataType>::Iterator::operator!=(Node* it) const
{
	return node_ptr != it;
}

template<typename DataType>
inline bool SingleLinked_list_with_head<DataType>::Iterator::operator<(Node* it) const
{
	return node_ptr < it;
}

template<typename DataType>
inline bool SingleLinked_list_with_head<DataType>::Iterator::operator<=(Node* it) const
{
	return node_ptr <= it;
}

template<typename DataType>
inline bool SingleLinked_list_with_head<DataType>::Iterator::operator>(Node* it) const
{
	return node_ptr > it;
}

template<typename DataType>
inline bool SingleLinked_list_with_head<DataType>::Iterator::operator>=(Node* it) const
{
	return node_ptr >= it;
}

template<typename DataType>
inline void SingleLinked_list_with_head<DataType>::Iterator::set(Node* node)
{
	if (node_ptr != node)
	{
		if (node_ptr)
		{
			delete node_ptr;
		}if (node)
		{
			node_ptr = new Node;
			node_ptr->data = node->data;
			node_ptr->Next = node->Next;
		}
	}
}

//单链表实现

template<typename DataType>
inline SingleLinked_list_with_head<DataType>::SingleLinked_list_with_head()
{
	head = Iterator(new Node);
	head.get()->data = DataType(); // 初始化头节点的数据
	head.get()->Next = nullptr;    // 初始化头节点的下一个指针
	last = head;                   // 初始化最后一个节点为头节点
	length = 0;
}
//默认尾插法
template<typename DataType>
inline SingleLinked_list_with_head<DataType>::SingleLinked_list_with_head(size_t length, const DataType& val)
{
	head = new Iterator();
	head.node_ptr->data = DataType();
	Node* current = head.node_ptr;
	for (size_t i = 0; i < length; ++i)
	{
		Node* newNode = new Node;
		newNode->data = val;
		newNode->Next = nullptr;
		current->Next = newNode;
		current = current->Next;
	}
	current->Next = nullptr;
	//如果这里出错，则是因为重载该赋值运算符 有问题！！！！
	last = current;
}

#endif // !SINGLE_LINKED_LIST
