#pragma once
#include "common.h"
void func(/*TestA a,*/ TestA aa)
{
	std::cout << "func start " << &aa << std::endl;
	//a.set_data(9999);
	aa.set_data(8888);
	//a.print();
	//a.print(101);
	//aa.print(102);
	std::cout << "func end " << &aa << std::endl;
}

void TestA::print_offset()
{
	std::cout << "offset = " << &(((TestA *)0)->number) << std::endl;
}
