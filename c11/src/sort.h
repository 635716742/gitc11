#pragma once
#include <vector>
typedef std::vector<int> vec_int;

namespace my_sort
{
	//ð��:�ڲ�ѭ��ÿ�����������ź��棨O(n^2)��
	void bubble_sort(vec_int& array);
	void bubble_sort1(vec_int& array);
}
