#include "leetcode.h"


bool LC::leet_code4(const Int_Matrix& matrix, int target)
{
	//1 2 3种方法本质上没有区别
#if LC4_METHOD == 1
	if (matrix.size() <= 0 || matrix[0].size() <= 0)
	{
		return false;
	}
	int rows = matrix.size();
	for (auto i = 0; i < matrix.size();++i)
	{
		for (auto j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j] == target)
			{
				return true;
			}
		}
	}
#elif LC4_METHOD == 2
	for (auto i = 1; i <= matrix.size(); ++i)
	{
		for (auto j = 1; j < matrix[i - 1].size(); ++j)
		{
			if (target < matrix[i - 1][j - 1] || (target > matrix[i - 1][j - 1] && target < matrix[i - 1][j]))
			{
				break;
			}

			if (target == matrix[i - 1][j - 1] || target == matrix[i - 1][j])
			{
				return true;
			}
		}
	}
#elif LC4_METHOD == 3
//中线最坏的情况也是o（mn）
	auto i = 0;
	auto j = 0;
	while (i < matrix.size() && j < matrix[i].size())
	{
		if (target > matrix[i][j])
		{
			++i;
			++j;
			continue;
		}
		if (target == matrix[i][j])
		{
			return true;
		}
		for (auto m = j-1; m >= 0; --m)
		{
			if (target > matrix[i][m])
			{
				break;
			}
			if (target == matrix[i][m])
			{
				return true;
			}
		}
		for (auto m = i - 1; m >= 0; --m)
		{
			if (target > matrix[m][j])
			{
				break;
			}
			if (target == matrix[m][j])
			{
				return true;
			}
		}
		++i;
		++j;
	}
#elif LC4_METHOD == 4
	if (matrix.size() <= 0 || matrix[0].size() <= 0)
	{
		return false;
	}

	int rows = matrix.size() - 1;
	int lines = 0;
	while (rows >= 0 && lines < matrix[0].size())
	{
		if (matrix[rows][lines] == target)
		{
			return true;
		}
		else if (target > matrix[rows][lines])
		{
			++lines;
		}
		else
		{
			--rows;
		}
	}
#endif

	return false;
}

