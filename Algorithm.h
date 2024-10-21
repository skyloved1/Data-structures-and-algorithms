#pragma once
#include <ctime>
#include <cstdlib>
#include <list>
#include <mutex>
#include <shared_mutex>
#include <future>
template<typename T>
void  Fisher_Yates_Shuffle_Algorithm(T* arr, size_t arr_Length) {
	std::srand(time(0));
	for (size_t i = arr_Length - 1; i > 0; --i)
	{
		size_t rand_index = std::rand() % (i + 1);
		T temp = arr[i];
		arr[i] = arr[rand_index];
		arr[rand_index] = temp;
	}
}
template<typename T>
std::list<T> quick_sort(std::list<T> input) {
	if (input.size() <= 1) {
		return input;
	}

	T Axis_num = *(input.begin());
	std::list<T> group1;
	std::list<T> group2;

	auto it = input.begin();
	++it; // 跳过基准元素
	for (; it != input.end(); ++it) {
		if (*it < Axis_num) {
			group1.push_back(*it);
		}
		else {
			group2.push_back(*it);
		}
	}
	if (group1.size() < 1000)
	{
		group1 = quick_sort(group1);
	}
	else
	{
		auto g1_result = std::async(std::launch::async, quick_sort<T>, group1);
		group1 = g1_result.get();
	}

	if (group2.size() < 1000)
	{
		group2 = quick_sort(group2);
	}
	else
	{
		auto g2_result = std::async(std::launch::async, quick_sort<T>, group2);
		group2 = g2_result.get();
	}

	std::list<T> result;
	result.splice(result.end(), group1);
	result.push_back(Axis_num); // 将基准元素添加到结果中
	result.splice(result.end(), group2);

	return result;
}