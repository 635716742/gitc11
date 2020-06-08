#pragma once
#include <vector>
#include <string>

class my_algorithm
{
public:
	//假设有几种硬币，如1 5 10 20 50 100，并且数量无限。请找出能够组成某个数目的找零所使用最少的硬币数。
	int coin_max(int num);

	void get_next(const std::string& str, std::vector<int>& next);
private:
	int _coin_max(const int& coin_value, int& num);

};

