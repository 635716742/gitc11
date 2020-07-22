#pragma once
#include "common.h"
namespace mfoeward
{
	template <typename T>
	void func(const T a)
	{
		if (std::is_fundamental<T>::value)
		{
			std::cout << "func name *& :" << a << std::endl;
		}
		else
		{
			std::cout << "func name *&" << std::endl;
		}
	}

	template <typename T>
	void func(T* a)
	{
		if (std::is_fundamental<T>::value)
		{
			std::to_string(*a);
			std::cout << "func name * :" << a << std::endl;
		}
		else
		{
			std::cout << "func name *" << std::endl;
		}
	}

	template <typename T>
	void func(const T* a)
	{
		if (std::is_fundamental<T>::value)
		{
			std::to_string(*a);
			std::cout << "func name const * :" << a << std::endl;
		}
		else
		{
			std::cout << "func name const *" << std::endl;
		}
	}

	//template <typename T>
	//void func(T& a)
	//{
	//	if (std::is_pointer<T>::value)
	//	{
	//		std::cout << "pointer &" << std::endl;
	//		return;
	//	}
	//	if (std::is_fundamental<T>::value)
	//	{
	//		//std::to_string(a);
	//		std::cout << "func name & :" << a << std::endl;
	//	}
	//	else
	//	{
	//		std::cout << "func name &" << std::endl;
	//	}
	//}

	//template <typename T>
	//void func(const T& a)
	//{
	//	if (std::is_pointer<T>::value)
	//	{
	//		std::cout << "const pointer &" << std::endl;
	//		return;
	//	}
	//	if (std::is_fundamental<T>::value)
	//	{
	//		//std::to_string(a);
	//		std::cout << "const func name & :" << a << std::endl;
	//	}
	//	else
	//	{
	//		std::cout << "const func name &" << std::endl;
	//	}
	//}

	//template <typename T>
	//void func(const T&& a)
	//{
	//	if (std::is_fundamental<T>::value)
	//	{
	//		std::to_string(a);
	//		std::cout << "func name && :" << a << std::endl;
	//	}
	//	else
	//	{
	//		std::cout << "func name &" << std::endl;
	//	}
	//}

}
