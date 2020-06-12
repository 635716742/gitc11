#pragma once
#include "../common.h"
namespace refls {
	//得到变量的偏移
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
	//根据参数名字得到偏移
	//序列化
}
