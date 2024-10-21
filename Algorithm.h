#pragma once
#include <ctime>
#include <cstdlib>
#include <list>
#include <mutex>
#include <shared_mutex>
#include <future>
#include <queue>
//Fisher_Yates随机不重复洗牌算法
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
//快速排序
//当数据量超过1000时采用异步多线程处理
//TODO 应当使用线程池
// 来真正提升运行速度此时的速度与普通版本差不多，后续需要改进，
template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input, size_t per_thread_process_num) {
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
	if (group1.size() < per_thread_process_num)
	{
		group1 = parallel_quick_sort(group1, per_thread_process_num);
	}
	else
	{
		auto g1_result = std::async(std::launch::async, parallel_quick_sort<T>, group1, per_thread_process_num);
		group1 = g1_result.get();
	}

	if (group2.size() < per_thread_process_num)
	{
		group2 = parallel_quick_sort(group2, per_thread_process_num);
	}
	else
	{
		auto g2_result = std::async(std::launch::async, parallel_quick_sort<T>, group2, per_thread_process_num);
		group2 = g2_result.get();
	}

	std::list<T> result;
	result.splice(result.end(), group1);
	result.push_back(Axis_num); // 将基准元素添加到结果中
	result.splice(result.end(), group2);

	return result;
}

//AI 参考
//class ThreadPool {
//public:
//	ThreadPool(size_t num_threads);
//	~ThreadPool();
//	void enqueue(std::function<void()> task);
//
//private:
//	std::vector<std::thread> workers;
//	std::queue<std::function<void()>> tasks;
//	std::mutex queue_mutex;
//	std::condition_variable condition;
//	bool stop;
//};
//
//ThreadPool::ThreadPool(size_t num_threads) : stop(false) {
//	for (size_t i = 0; i < num_threads; ++i) {
//		workers.emplace_back([this] {
//			for (;;) {
//				std::function<void()> task;
//				{
//					std::unique_lock<std::mutex> lock(this->queue_mutex);
//					this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
//					if (this->stop && this->tasks.empty()) return;
//					task = std::move(this->tasks.front());
//					this->tasks.pop();
//				}
//				task();
//			}
//			});
//	}
//}
//
//ThreadPool::~ThreadPool() {
//	{
//		std::unique_lock<std::mutex> lock(queue_mutex);
//		stop = true;
//	}
//	condition.notify_all();
//	for (std::thread& worker : workers) worker.join();
//}
//
//void ThreadPool::enqueue(std::function<void()> task) {
//	{
//		std::unique_lock<std::mutex> lock(queue_mutex);
//		tasks.emplace(task);
//	}
//	condition.notify_one();
//}
//
//template<typename T>
//std::list<T> parallel_quick_sort(std::list<T> input, size_t per_thread_process_num, ThreadPool& pool) {
//	if (input.size() <= 1) {
//		return input;
//	}
//
//	T Axis_num = *(input.begin());
//	std::list<T> group1;
//	std::list<T> group2;
//
//	auto it = input.begin();
//	++it; // 跳过基准元素
//	for (; it != input.end(); ++it) {
//		if (*it < Axis_num) {
//			group1.push_back(*it);
//		}
//		else {
//			group2.push_back(*it);
//		}
//	}
//
//	std::future<std::list<T>> g1_result;
//	if (group1.size() < per_thread_process_num) {
//		group1 = parallel_quick_sort(group1, per_thread_process_num, pool);
//	}
//	else {
//		g1_result = std::async(std::launch::async, [&]() { return parallel_quick_sort(group1, per_thread_process_num, pool); });
//	}
//
//	std::future<std::list<T>> g2_result;
//	if (group2.size() < per_thread_process_num) {
//		group2 = parallel_quick_sort(group2, per_thread_process_num, pool);
//	}
//	else {
//		g2_result = std::async(std::launch::async, [&]() { return parallel_quick_sort(group2, per_thread_process_num, pool); });
//	}
//
//	if (g1_result.valid()) group1 = g1_result.get();
//	if (g2_result.valid()) group2 = g2_result.get();
//
//	std::list<T> result;
//	result.splice(result.end(), group1);
//	result.push_back(Axis_num); // 将基准元素添加到结果中
//	result.splice(result.end(), group2);
//
//	return result;
//}

//快速排序 (非多线程版)
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

	group1 = quick_sort(group1);
	group2 = quick_sort(group2);

	std::list<T> result;
	result.splice(result.end(), group1);
	result.push_back(Axis_num); // 将基准元素添加到结果中
	result.splice(result.end(), group2);

	return result;
}