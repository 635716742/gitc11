#include "sort.h"
namespace my_sort
{

	void bubble_sort(vec_int& array)
	{
		auto len = array.size();
		for (auto i = 0; i < len; ++i)
		{
			for (auto j = 0; j < len - 1 -i; ++j)
			{
				if (array[j] > array[j+1])
				{
					std::swap(array[j], array[j + 1]);
				}
			}
		}
	}

	void bubble_sort1(vec_int& array)
	{
		bool bflag = false;
		auto len = array.size();
		for (auto i = 0; i < len; ++i)
		{
			bflag = false;
			for (auto j = 0; j < len - 1 - i; ++j)
			{
				if (array[j] > array[j + 1])
				{
					bflag = true;
					std::swap(array[j], array[j + 1]);
				}
			}

			if (!bflag)
			{
				break;
			}
		}
	}

}