#pragma once
#include <ctime>
#include <cstdlib>

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