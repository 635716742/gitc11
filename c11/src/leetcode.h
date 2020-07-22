#pragma once
#include "common.h"
//leetcode
namespace LC
{
	typedef std::vector<std::vector<int> > Int_Matrix;
	const Int_Matrix g_mastrix = {
		{1,   4,  7, 11, 15},
		{2,   5,  8, 12, 19},
		{3,   6,  9, 16, 22},
		{10, 13, 14, 17, 24},
		{18, 21, 23, 26, 30}
	};

	//��һ�� n * m �Ķ�ά�����У�ÿһ�ж����մ����ҵ�����˳������ÿһ�ж����մ��ϵ��µ�����˳�����������һ������������������һ����ά�����һ���������ж��������Ƿ��и�������
	#define LC4_METHOD 4
	bool leet_code4(const Int_Matrix& matrix, int target);
}