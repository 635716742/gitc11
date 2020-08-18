#pragma once
#include <vector>
typedef std::vector<int> vec_int;

//所有都由小到大
namespace my_sort
{
	//冒泡:内层循环每次拿最大的数放后面（O(n^2)）
	void bubble_sort(vec_int& array);
	void bubble_sort1(vec_int& array);

	//插入:内层循环认为之前的数据是有序的（O(n^2)）
	void insert_sort(vec_int& array);
	//折半插入：就是插入 + 二分查找
	void half_insert_sort(vec_int& array);
}
