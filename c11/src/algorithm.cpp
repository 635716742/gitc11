#include "algorithm.h"
#include <iostream>
#include <limits>

int my_algorithm::coin_max(int num)
{
#if 1
	std::vector<int> coin_value = { 100, 50, 20, 10, 5, 1 };
	int n = 0;
	int dynamic_num = num;
	for (auto iter : coin_value)
	{
		int count = _coin_max(iter, dynamic_num);
		if (count < 0)
		{
			return 0;
		}
		n += count;
	}
	return n;
#else

	std::vector<int> c(num + 1, 0);
	for (int i = 1; i <= num; i++)
	{
		if (i == 1 || i == 5 || i == 10 || i == 20 || i == 50 || i == 100)
		{
			c[i] = 1;
			continue;
		}
		int curMin = std::numeric_limits<int>::max();
		if (i - 1 > 0)
			curMin = c[i - 1] < curMin ? c[i - 1] : curMin;
		if (i - 5 > 0)
			curMin = c[i - 5] < curMin ? c[i - 5] : curMin;
		if (i - 10 > 0)
			curMin = c[i - 10] < curMin ? c[i - 10] : curMin;
		if (i - 20 > 0)
			curMin = c[i - 20] < curMin ? c[i - 20] : curMin;
		if (i - 50 > 0)
			curMin = c[i - 50] < curMin ? c[i - 50] : curMin;
		if (i - 100 > 0)
			curMin = c[i - 100] < curMin ? c[i - 100] : curMin;
		c[i] = curMin + 1;
		std::cout << i << ":" <<c[i] << std::endl;
	} 
	return 0;
#endif
}

int my_algorithm::_coin_max(const int& coin_value, int& num)
{
	if (coin_value <= 0 || num <= 0)
	{
		return -1;
	}
	if (num >= coin_value)
	{
		int rem = (int)(num / coin_value);
		num -= (rem * coin_value);
		return rem;
	}
	return 0;
}

void my_algorithm::get_next(const std::string& str, std::vector<int>& next)
{
	if (str.size() < 1)
	{
		return; 
	}
	next.resize(str.size() + 1, 0);
	size_t i = 1; 
	size_t j = 0;
	next[1] = 0;
	while (i < str.size())
	{
		if (j == 0 || str[i] == str[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
}

void my_algorithm::pre_traverse(const tn_intptr root, vec_int& target)
{
	if (!root)
	{
		return;
	}
	target.push_back(root->value);
	pre_traverse(root->left, target);
	pre_traverse(root->right, target);
}

void my_algorithm::middle_traverse(const tn_intptr root, vec_int& target)
{
	if (!root)
	{
		return;
	}
	pre_traverse(root->left, target);
	target.push_back(root->value);
	pre_traverse(root->right, target);
}

void my_algorithm::back_traverse(const tn_intptr root, vec_int& target)
{
	if (!root)
	{
		return;
	}
	pre_traverse(root->left, target);
	pre_traverse(root->right, target);
	target.push_back(root->value);
}
