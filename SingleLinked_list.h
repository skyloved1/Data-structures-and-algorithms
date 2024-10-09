#pragma once
#ifndef SINGLE_LINKED_LIST
#define SINGLE_LINKED_LIST
#include <initializer_list>
#include <iostream>
//pos指的是按位，即第几个
//单链表带头节点的实现

template<typename DataType>
class SingleLinked_list_with_head
{
private:
	struct Node
	{
		DataType data;
		Node* Next;
	};
	size_t length;
	Node* head;
	Node* last;
	//Node* index_arr[];
public:
	using Node_ptr = Node*;
	//默认构造函数 仅初始化头节点
	SingleLinked_list_with_head();
	//初始化长度为n的链表，其值为val
	SingleLinked_list_with_head(size_t length, const  DataType& val = DataType());
	//支持初始化列表
	SingleLinked_list_with_head(std::initializer_list<DataType> list);
	//提供两个迭代器来表示范围，把数组变为链表
	SingleLinked_list_with_head<DataType>(DataType* _first, DataType* _last);
	//复制构造函数
	SingleLinked_list_with_head(SingleLinked_list_with_head<DataType>& L);
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
	bool insert_still_sequence_by_asc(DataType val);
	//TODO 逆置单链表
	void reverse_list();
	template<typename Fn_bool>
	size_t select_val(Fn_bool Function);		//按值查找

	//common method
	bool delete_node(size_t pos);
	bool delete_node(size_t pos_begin, size_t pos_end);
	Node& get_node(size_t pos);										//按位查找
	const Node& get_node(size_t pos)const;										//按位查找
	bool push_back(const DataType& val);
	bool push_front(const DataType& val);
	DataType pop_back();
	DataType pop_front();
	void display();

	bool isEmpty() const;
	void copy_to_arr(DataType* _first, DataType* _lase);
	size_t getLength()const;
	Node* getHead()const;
	Node* getEnd()const;
};

//单链表实现

template<typename DataType>
inline SingleLinked_list_with_head<DataType>::SingleLinked_list_with_head()
{
	head = new Node;
	//如果这里出错，则是 get方法有误！
	head->data = DataType(); // 初始化头节点的数据
	head->Next = nullptr;    // 初始化头节点的下一个指针
	last = head;                   // 初始化最后一个节点为头节点
	length = 0;
}
//默认尾插法
template<typename DataType>
inline SingleLinked_list_with_head<DataType>::SingleLinked_list_with_head(size_t length, const DataType& val) : SingleLinked_list_with_head()
{
	Node* current = head;
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

	this->length = length;
}

template<typename DataType>
inline SingleLinked_list_with_head<DataType>::SingleLinked_list_with_head(std::initializer_list<DataType> list) :SingleLinked_list_with_head()
{
	Node* currentNode = head;
	for (auto X : list)
	{
		Node* newNode = new Node();
		newNode->data = X;
		newNode->Next = nullptr;
		currentNode->Next = newNode;
		currentNode = currentNode->Next;
	}
	last = currentNode;
	length = list.size();
}
template<typename DataType>
inline SingleLinked_list_with_head<DataType>::SingleLinked_list_with_head(SingleLinked_list_with_head<DataType>& L) :SingleLinked_list_with_head()
{
	Node* currentNode = head;
	Node* it = L.head->Next; // 修改这里，确保 it 指向 L 的第一个有效节点
	for (size_t i = 0; i < L.length; ++i)
	{
		Node* newNode = new Node();
		newNode->data = it->data;
		newNode->Next = nullptr;
		currentNode->Next = newNode;
		currentNode = currentNode->Next;
		it = it->Next;
	}
	last = currentNode;
	length = L.length;
}
template<typename DataType>
inline SingleLinked_list_with_head<DataType>::SingleLinked_list_with_head(SingleLinked_list_with_head<DataType>&& L)
{
	this->head = L.head;
	L.head = nullptr;
	this->last = L.last;
	L.last = nullptr;
	this->length = L.length;
	L.length = 0;
}
template<typename DataType>
inline SingleLinked_list_with_head<DataType>::~SingleLinked_list_with_head()
{
	Node* currentNode = head;
	while (currentNode != nullptr)
	{
		Node* temp = currentNode;
		currentNode = currentNode->Next;
		delete temp;
	}
	head = nullptr;
	last = nullptr;
	length = 0;
}
template<typename DataType>
inline bool SingleLinked_list_with_head<DataType>::head_insert(size_t pos, DataType val)
{
	Node* newNode = new Node;
	newNode->data = val;
	newNode->Next = nullptr;
	Node* currentNode = head->Next;
	Node* currentNode_prior = head;
	size_t count = 1;
	while (currentNode != nullptr && count != pos)
	{
		currentNode = currentNode->Next;
		currentNode_prior = currentNode_prior->Next;
		++count;
	}

	if (count == pos)
	{
		newNode->Next = currentNode_prior->Next;
		currentNode_prior->Next = newNode;
		if (newNode->Next == nullptr) // 如果新节点是最后一个节点，更新 last 指针
		{
			last = newNode;
		}
		++length;
		return true;
	}

	delete newNode; // 如果插入失败，删除新节点
	return false;
}
template<typename DataType>
inline bool SingleLinked_list_with_head<DataType>::tail_insert(size_t pos, DataType val)
{
	Node* newNode = new Node;
	newNode->data = val;
	newNode->Next = nullptr;
	Node* currentNode = head->Next;
	size_t count = 1;
	while (currentNode != nullptr && count != pos)
	{
		currentNode = currentNode->Next;
		++count;
	}
	if (count == pos)
	{
		newNode->Next = currentNode->Next;
		currentNode->Next = newNode;
		if (newNode->Next == nullptr)
		{
			last = newNode;
		}
		++length;
		return true;
	}
	delete newNode; // 如果插入失败，删除新节点
	return false;
}
template<typename DataType>
inline bool SingleLinked_list_with_head<DataType>::delete_first_val(DataType val)
{
	Node* currentNode = head->Next;
	Node* currentNode_prior = head;

	while (currentNode != nullptr)
	{
		if (currentNode->data == val)
		{
			currentNode_prior->Next = currentNode->Next;
			delete currentNode;
			--length;
			return true;
		}
		currentNode_prior = currentNode_prior->Next;
		currentNode = currentNode->Next;
	}

	return false; // 如果未找到节点，返回 false
}
template<typename DataType>
inline bool SingleLinked_list_with_head<DataType>::delete_all_val(DataType val)
{
	Node* currentNode = head->Next;
	Node* currentNode_prior = head;
	bool found = false;
	while (currentNode != nullptr)
	{
		if (currentNode->data == val)
		{
			currentNode_prior->Next = currentNode->Next;
			delete currentNode;
			--length;
			currentNode = currentNode_prior->Next;
			found = true;
		}
		else
		{
			currentNode_prior = currentNode_prior->Next;
			currentNode = currentNode->Next;
		}
	}

	return found; // 如果未找到节点，返回 false
}
template<typename DataType>
inline bool SingleLinked_list_with_head<DataType>::insert_still_sequence_by_asc(DataType val)
{
	Node* currentNode = head->Next;
	Node* currentNode_prior = head;
	Node* newNode = new Node;
	newNode->data = val;
	newNode->Next = nullptr;
	while (currentNode != nullptr) {
		if (currentNode->data >= val)
		{
			newNode->Next = currentNode;
			currentNode_prior->Next = newNode;
			return true;
		}
		currentNode_prior = currentNode_prior->Next;
		currentNode = currentNode->Next;
	}
	// 如果遍历到链表末尾仍未找到合适位置，将新节点插入到链表末尾
	if (currentNode == nullptr)
	{
		currentNode_prior->Next = newNode;
		last = newNode;
		++length;
		return true;
	}

	return false;
}
template<typename DataType>
inline void SingleLinked_list_with_head<DataType>::reverse_list()
{
	if (head == nullptr || head->Next == nullptr) {
		// 如果链表为空或只有一个节点，则无需反转
		return;
	}
	Node* temp = head->Next;
	Node* currentNode = head->Next;
	Node* priorNode = nullptr;
	Node* nextNode = nullptr;
	while (currentNode != nullptr)
	{
		nextNode = currentNode->Next;
		currentNode->Next = priorNode;
		priorNode = currentNode;
		currentNode = nextNode;
	}

	head->Next = last;
	last = temp;
}
template<typename DataType>
inline SingleLinked_list_with_head<DataType>::SingleLinked_list_with_head(DataType* _first, DataType* _last) : SingleLinked_list_with_head()
{
	Node* currentNode = head;
	size_t count = 0;
	for (auto it = _first; it != _last; ++it)
	{
		Node* newNode = new Node();
		newNode->data = *it;
		newNode->Next = nullptr;
		currentNode->Next = newNode;
		currentNode = currentNode->Next;
		++count;
	}
	last = currentNode;
	length = count;
}
template<typename DataType>
template<typename Fn_bool>
inline size_t SingleLinked_list_with_head<DataType>::select_val(Fn_bool Function)
{
	Node* currentNode = head->Next;
	size_t count = 1;
	while (currentNode != nullptr)
	{
		if (Function(currentNode->data))
		{
			return count;
		}
		currentNode = currentNode->Next;
		++count;
	}
	return 0;
}
// 删除指定位置的节点
template<typename DataType>
bool SingleLinked_list_with_head<DataType>::delete_node(size_t pos) {
	if (pos < 1 || pos > length) {
		return false; // 位置无效
	}

	Node* currentNode = head;
	for (size_t i = 1; i < pos; ++i) {
		currentNode = currentNode->Next;
	}

	Node* nodeToDelete = currentNode->Next;
	currentNode->Next = nodeToDelete->Next;
	delete nodeToDelete;
	--length;

	if (currentNode->Next == nullptr) {
		last = currentNode; // 更新最后一个节点
	}

	return true;
}

// 删除指定范围的节点
template<typename DataType>
bool SingleLinked_list_with_head<DataType>::delete_node(size_t pos_begin, size_t pos_end) {
	if (pos_begin < 1 || pos_end > length || pos_begin > pos_end) {
		return false; // 位置无效
	}

	Node* currentNode = head;
	for (size_t i = 1; i < pos_begin; ++i) {
		currentNode = currentNode->Next;
	}

	Node* nodeToDelete = currentNode->Next;
	for (size_t i = pos_begin; i <= pos_end; ++i) {
		Node* temp = nodeToDelete;
		nodeToDelete = nodeToDelete->Next;
		delete temp;
		--length;
	}

	currentNode->Next = nodeToDelete;

	if (nodeToDelete == nullptr) {
		last = currentNode; // 更新最后一个节点
	}

	return true;
}

// 按位查找节点
template<typename DataType>
typename SingleLinked_list_with_head<DataType>::Node& SingleLinked_list_with_head<DataType>::get_node(size_t pos) {
	if (pos < 1 || pos > length) {
		throw std::out_of_range("位置无效");
	}

	Node* currentNode = head->Next;
	for (size_t i = 1; i < pos; ++i) {
		currentNode = currentNode->Next;
	}

	return *currentNode;
}

// 按位查找节点（常量版本）
template<typename DataType>
const typename SingleLinked_list_with_head<DataType>::Node& SingleLinked_list_with_head<DataType>::get_node(size_t pos) const {
	if (pos < 1 || pos > length) {
		throw std::out_of_range("位置无效");
	}

	Node* currentNode = head->Next;
	for (size_t i = 1; i < pos; ++i) {
		currentNode = currentNode->Next;
	}

	return *currentNode;
}

// 在链表末尾添加节点
template<typename DataType>
bool SingleLinked_list_with_head<DataType>::push_back(const DataType& val) {
	Node* newNode = new Node;
	newNode->data = val;
	newNode->Next = nullptr;

	if (head == nullptr) {
		head = newNode;
		last = newNode;
	}
	else {
		last->Next = newNode;
		last = newNode;
	}

	++length;
	return true;
}

// 在链表头部添加节点
template<typename DataType>
bool SingleLinked_list_with_head<DataType>::push_front(const DataType& val) {
	Node* newNode = new Node;
	newNode->data = val;
	newNode->Next = head->Next;
	head->Next = newNode;

	if (last == head) {
		last = newNode;
	}

	++length;
	return true;
}

// 删除链表末尾的节点并返回其值
template<typename DataType>
DataType SingleLinked_list_with_head<DataType>::pop_back() {
	if (isEmpty()) {
		throw std::out_of_range("链表为空");
	}

	Node* currentNode = head;
	while (currentNode->Next != last) {
		currentNode = currentNode->Next;
	}

	DataType val = last->data;
	delete last;
	last = currentNode;
	currentNode->Next = nullptr;
	--length;

	return val;
}

// 删除链表头部的节点并返回其值
template<typename DataType>
DataType SingleLinked_list_with_head<DataType>::pop_front() {
	if (isEmpty()) {
		throw std::out_of_range("链表为空");
	}

	Node* nodeToDelete = head->Next;
	DataType val = nodeToDelete->data;
	head->Next = nodeToDelete->Next;
	delete nodeToDelete;
	--length;

	if (head->Next == nullptr) {
		last = head;
	}

	return val;
}

template<typename DataType>
inline void SingleLinked_list_with_head<DataType>::display()
{
	Node* currentNode = head->Next;
	while (currentNode != nullptr)
	{
		std::cout << currentNode->data << "   ";
		currentNode = currentNode->Next;
	}
}

// 判断链表是否为空
template<typename DataType>
bool SingleLinked_list_with_head<DataType>::isEmpty() const {
	return length == 0;
}

// 将链表复制到数组
template<typename DataType>
void SingleLinked_list_with_head<DataType>::copy_to_arr(DataType* _first, DataType* _last) {
	Node* currentNode = head->Next;
	size_t count = 0;
	while (currentNode != nullptr && _first != _last)
	{
		*_first = currentNode->data;
		currentNode = currentNode->Next;
		++count;
		++_first;
	}
}

// 获取链表长度
template<typename DataType>
size_t SingleLinked_list_with_head<DataType>::getLength() const {
	return length;
}

// 获取头部指针
template<typename DataType>
inline typename SingleLinked_list_with_head<DataType>::Node* SingleLinked_list_with_head<DataType>::getHead() const
{
	return head;
}

// 获取尾部指针
template<typename DataType>
typename SingleLinked_list_with_head<DataType>::Node* SingleLinked_list_with_head<DataType>::getEnd() const {
	return  last;
}
;

#endif // !SINGLE_LINKED_LIST
