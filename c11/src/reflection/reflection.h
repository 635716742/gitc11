#pragma once
#include "../common.h"
namespace refls {
	//�õ�������ƫ��
	struct refOffset 
	{
		char c_offset;
		int  i_offset;
	};

	struct TestOffset
	{
		int i_offset;
		std::string str_offset;
		std::vector<int> vec_offset;
		refOffset m_refoffset;


	};
	//���ݲ������ֵõ�ƫ��
	//���л�
}
