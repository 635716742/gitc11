#pragma once
#include <vector>
typedef std::vector<int> vec_int;

//���ж���С����
namespace my_sort
{
	//ð��:�ڲ�ѭ��ÿ�����������ź��棨O(n^2)��
	void bubble_sort(vec_int& array);
	void bubble_sort1(vec_int& array);

	//����:�ڲ�ѭ����Ϊ֮ǰ������������ģ�O(n^2)��
	void insert_sort(vec_int& array);
	//�۰���룺���ǲ��� + ���ֲ���
	void half_insert_sort(vec_int& array);
}
