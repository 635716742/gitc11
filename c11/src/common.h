#pragma once
#include <stdio.h>
#include <iostream>
#include <future>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <string>
#include <memory>

#define print_separator(a) \
	if(std::is_same<int, decltype(a)>::value)\
		std::cout << "·Ö¸ô·û" << std::to_string(a).c_str() <<std::endl;\

template <typename T>
void print_vec(std::vector<T> vec)
{
}

template <typename T = int>
void print_vec(std::vector<int> vec)
{
	for (auto iter : vec)
	{
		std::cout << iter << " ";
	}
	std::cout << "print end" << std::endl;
}

template <typename T = std::vector<int> >
void print_vec(std::vector< std::vector<int> > vec)
{
	for (auto iter : vec)
	{
		for (auto j : iter)
		{
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "print end" << std::endl;
}

class TestA
{
public:
	TestA() {
		std::cout << this << ",create name is TastA " << std::endl;
		data = std::make_shared<int>(10);
		number = 11;
	};
	~TestA() {
		std::cout << this <<",level name is TastA " << *data << ",count = " << data.use_count() << std::endl;
		data.reset();
		//if (data)
		//{
		//	delete data;
		//	data = NULL;
		//}
	};
	TestA(const TestA& cl)
	{
		std::cout << &cl << " to " <<this << ",copy name is TastA " << std::endl;
		data = cl.data;
		number = cl.number;
	};

	TestA& operator=(const TestA& cl)
	{
		std::cout << "equal name is TastA " << std::endl;
	}

	void print()
	{
		if (data)
		{
			std::cout << *data << std::endl;
		}
	}
	void print(int&& n)
	{
		std::cout << "n = " << n <<std::endl;
	}

	void print(const int&& n)
	{
		std::cout << "n = " << n << std::endl;
	}

	void set_data(const int num)
	{
		*data = num;
		number = num;
	}
	int get_data()
	{
		if (data)
			return *data;
		return 0;
	}
	int get_num()
	{
		return number;
	}

	void print_offset();
private:
	std::shared_ptr<int> data;
	int number;
};

void func(/*TestA a,*/ TestA aa);

inline int add(int a, int b)
{
	std::cout << "implement add" << std::endl;
	return a + b;
};

static int g_add = add(3 , 4);