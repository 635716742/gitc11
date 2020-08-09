#pragma once
#include <vector>
typedef std::vector<int> vec_int;

namespace my_sort
{
	//冒泡:内层循环每次拿最大的数放后面（O(n^2)）
	void bubble_sort(vec_int& array);
	void bubble_sort1(vec_int& array);
}
