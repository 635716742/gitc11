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

	void insert_sort(vec_int& array)
	{
		auto len = array.size();
		if (len < 2)
		{
			return;
		}
		for (int i = 1; i < len; ++i)
		{
			int index = i;
			for (auto j = i - 1;j >= 0;j--)
			{
				if (array[index] < array[j])
				{
					std::swap(array[index], array[j]);
					index = j;
				}
				else
				{
					break;
				}
			}
		}
	}

	void half_insert_sort(vec_int& array)
	{
		auto len = array.size();
		if (len < 2)
		{
			return;
		}
		for (int i = 1; i < len; ++i)
		{
			int low = 0;
			int high = i - 1;
			while (low <= high)
			{
				int mid = ((low + high) / 2);
				if (array[mid] > array[i])
				{
					high = mid - 1;
				}
				else
				{
					low = mid + 1;
				}
			}
			int index = i; //£¿hight+1
			for (auto j = i - 1; j >= high + 1; j--)
			{
				if (array[index] < array[j])
				{
					std::swap(array[index], array[j]);
					index = j;
				}
				else
				{
					break;
				}
			}
		}
	}

}