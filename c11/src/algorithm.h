#pragma once
#include <vector>
#include <string>

class my_algorithm
{
public:
	//�����м���Ӳ�ң���1 5 10 20 50 100�������������ޡ����ҳ��ܹ����ĳ����Ŀ��������ʹ�����ٵ�Ӳ������
	int coin_max(int num);

	void get_next(const std::string& str, std::vector<int>& next);
private:
	int _coin_max(const int& coin_value, int& num);

};

