#pragma once
#include <type_traits>
namespace MyTest
{
	class A
	{
	public:
		A() {};
	};

	class B : A
	{
	public:
		B() {};
	};

	class C
	{
	public:
		C() {};
	};

	template<class T>
	typename std::enable_if<std::is_base_of<A, T>::value>::type //·ÀÖ¹´«²Î´íÎó
		SetClass(T* pp)
	{
		std::cout << "cout set class value" << std::endl;
	};
};
