#pragma once
#include <iostream>

/*traits作用：
1、需要某个函数的返回值类型做逻辑判断（想要知道任意函数的返回值类型）；
2、需要一个返回值是某类的某成员的模板函数；（typename和class）
template <class T>
struct unknown_class_traits {
typedef typename T::return_type return_type;
};
*/
////////////////////////////////////1//////////////////////////////////////
template<typename Inherited>
class COM_Impl : public Inherited
{
public:
	COM_Impl()
	{
		std::cout << "create my name is COM_Impl" << std::endl;
	}

	//virtual void print()
	//{
	//	std::cout << __FUNCTION__  << "my name is print" << std::endl;
	//}
};

template<class Inherited>
struct RMI_Wrapper 
{
	enum { CLSID = 0, IS_PLAYER = 0 };

	RMI_Wrapper()
	{
		new Inherited;
		std::cout << "create my name is RMI_Wrapper" << std::endl;
	}

	//void print()
	//{
	//	std::cout << __FUNCTION__ <<"my name is RMI_Wrapper" << std::endl;
	//}
};

//
template<typename ImplType>
class ComponentConstructor
{
	typedef RMI_Wrapper<COM_Impl< ImplType > > ImpT;
public:

	ImplType * Create()
	{
		std::cout << "ComponentConstructor create start" << std::endl;
		ImpT* model = new ImpT(); //RMI_Wrapper 必须重载后的 否则是个error
		std::cout << "ComponentConstructor create end"<< std::endl;
		return (ImplType*)model;
	}
};

class ObjAManager
{
public:
	ObjAManager()
	{
		std::cout << "my name is ObjAManager" << std::endl;
	}
	void print()
	{
		std::cout << "print my name is ObjAManager" << m_count++ << std::endl;
	}

	void print1()
	{
		std::cout << "print my name is ObjAManager:" << m_count++ << std::endl;
	}

public:
	int m_count = 0;
};
///////////////////////////////////1///////////////////////////////////////

///////////////////////////////////2///////////////////////////////////////
//给类注册一个id
template<class TInterface>
struct iidof_t
{
};
#define DECLARE_BIBO_GUID(name, id) \
const DWORD IID_##name = id; \
template<> \
struct iidof_t<name> \
{ \
	enum {value = IID_##name,}; \
}; \

#define iidof(type) iidof_t<type>::value
///////////////////////////////////2///////////////////////////////////////

///////////////////////////////////3///////////////////////////////////////
//typename 的二义性
class Test_1
{
public:
	static const int TS = 1;
};

class Test_2
{
public:
	struct TS
	{
		int value;
	};
};

template
< class T >
void test_class()
{
	typename T::TS * a;        // 1. 通过泛指类型 T 内部的数据类型 TS 定义指针变量 a （推荐的解读方式）
							   // 2. 使用泛指类型 T 内部的静态成员变量 TS 与全局变量 a 进行乘法操作
							   // 不加typename是第二种情况
}

///////////////////////////////////3///////////////////////////////////////

///////////////////////////////////4///////////////////////////////////////
//函数 trait
template<typename Function> struct memfun_trait_helper;

template<typename Class, typename R>
struct memfun_trait_helper<R(Class::*)(void)>
{
	typedef R(Class::*function_type)(void);
	typedef Class class_type;
	enum { arity = 0 };
	typedef R result_type;
};

template<typename Class, typename R, typename T1>
struct memfun_trait_helper<R(Class::*)(T1)>
{
	typedef R(Class::*function_type)(T1);
	typedef Class class_type;
	enum { arity = 1 };
	typedef R result_type;
	typedef T1 arg1_type;
};

template<typename Class, typename R, typename T1, typename T2>
struct memfun_trait_helper<R(Class::*)(T1, T2)>
{
	typedef R(Class::*function_type)(T1, T2);
	typedef Class class_type;
	enum { arity = 2 };
	typedef R result_type;
	typedef T1 arg1_type;
	typedef T2 arg2_type;
};

//template<typename Class, typename R, typename T1, typename T2, typename T3>
//struct memfun_trait_helper<R(Class::*)(T1, T2, T3)>
//{
//	typedef R(Class::*function_type)(T1, T2, T3);
//	typedef Class class_type;
//	enum { arity = 3 };
//	typedef R result_type;
//	typedef T1 arg1_type;
//	typedef T2 arg2_type;
//	typedef T3 arg3_type;
//};
//
//template<typename Class, typename R, typename T1, typename T2, typename T3, typename T4>
//struct memfun_trait_helper<R(Class::*)(T1, T2, T3, T4)>
//{
//	typedef R(Class::*function_type)(T1, T2, T3, T4);
//	typedef Class class_type;
//	enum { arity = 4 };
//	typedef R result_type;
//	typedef T1 arg1_type;
//	typedef T2 arg2_type;
//	typedef T3 arg3_type;
//	typedef T4 arg4_type;
//};
//
//template<typename Class, typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
//struct memfun_trait_helper<R(Class::*)(T1, T2, T3, T4, T5)>
//{
//	typedef R(Class::*function_type)(T1, T2, T3, T4, T5);
//	typedef Class class_type;
//	enum { arity = 5 };
//	typedef R result_type;
//	typedef T1 arg1_type;
//	typedef T2 arg2_type;
//	typedef T3 arg3_type;
//	typedef T4 arg4_type;
//	typedef T5 arg5_type;
//};
//
//template<typename Class, typename R, typename T1, typename T2, typename T3, typename T4, typename T5
//	, typename T6>
//	struct memfun_trait_helper<R(Class::*)(T1, T2, T3, T4, T5, T6)>
//{
//	typedef R(Class::*function_type)(T1, T2, T3, T4, T5, T6);
//	typedef Class class_type;
//	enum { arity = 6 };
//	typedef R result_type;
//	typedef T1 arg1_type;
//	typedef T2 arg2_type;
//	typedef T3 arg3_type;
//	typedef T4 arg4_type;
//	typedef T5 arg5_type;
//	typedef T6 arg6_type;
//};
//
//template<typename Class, typename R, typename T1, typename T2, typename T3, typename T4, typename T5
//	, typename T6, typename T7>
//	struct memfun_trait_helper<R(Class::*)(T1, T2, T3, T4, T5, T6, T7)>
//{
//	typedef R(Class::*function_type)(T1, T2, T3, T4, T5, T6, T7);
//	typedef Class class_type;
//	enum { arity = 7 };
//	typedef R result_type;
//	typedef T1 arg1_type;
//	typedef T2 arg2_type;
//	typedef T3 arg3_type;
//	typedef T4 arg4_type;
//	typedef T5 arg5_type;
//	typedef T6 arg6_type;
//	typedef T7 arg7_type;
//};
//
//template<typename Class, typename R, typename T1, typename T2, typename T3, typename T4, typename T5
//	, typename T6, typename T7, typename T8>
//	struct memfun_trait_helper<R(Class::*)(T1, T2, T3, T4, T5, T6, T7, T8)>
//{
//	typedef R(Class::*function_type)(T1, T2, T3, T4, T5, T6, T7, T8);
//	typedef Class class_type;
//	enum { arity = 8 };
//	typedef R result_type;
//	typedef T1 arg1_type;
//	typedef T2 arg2_type;
//	typedef T3 arg3_type;
//	typedef T4 arg4_type;
//	typedef T5 arg5_type;
//	typedef T6 arg6_type;
//	typedef T7 arg7_type;
//	typedef T8 arg8_type;
//};
//
//template<typename Class, typename R, typename T1, typename T2, typename T3, typename T4, typename T5
//	, typename T6, typename T7, typename T8, typename T9>
//	struct memfun_trait_helper<R(Class::*)(T1, T2, T3, T4, T5, T6, T7, T8, T9)>
//{
//	typedef R(Class::*function_type)(T1, T2, T3, T4, T5, T6, T7, T8, T9);
//	typedef Class class_type;
//	enum { arity = 9 };
//	typedef R result_type;
//	typedef T1 arg1_type;
//	typedef T2 arg2_type;
//	typedef T3 arg3_type;
//	typedef T4 arg4_type;
//	typedef T5 arg5_type;
//	typedef T6 arg6_type;
//	typedef T7 arg7_type;
//	typedef T8 arg8_type;
//	typedef T9 arg9_type;
//};
//
//template<typename Class, typename R, typename T1, typename T2, typename T3, typename T4, typename T5
//	, typename T6, typename T7, typename T8, typename T9, typename T10>
//	struct memfun_trait_helper<R(Class::*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)>
//{
//	typedef R(Class::*function_type)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10);
//	typedef Class class_type;
//	enum { arity = 10 };
//	typedef R result_type;
//	typedef T1 arg1_type;
//	typedef T2 arg2_type;
//	typedef T3 arg3_type;
//	typedef T4 arg4_type;
//	typedef T5 arg5_type;
//	typedef T6 arg6_type;
//	typedef T7 arg7_type;
//	typedef T8 arg8_type;
//	typedef T9 arg9_type;
//	typedef T10 arg10_type;
//};

template<typename Function>
struct memfun_trait :
	public memfun_trait_helper<Function>
{
};

template<typename T>
struct h3d_is_void
{
	enum { value = 0 };
};
template<>
struct h3d_is_void<void>
{
	enum { value = 1 };
};

template<typename ObjT, typename FuncT>
void RegisterFunction(ObjT* obj, FuncT func)
{
	typedef typename memfun_trait<FuncT>::result_type result_type;

	std::cout << "traits result type = " << h3d_is_void<result_type>::value << std::endl;
	std::cout << "traits param count = " << memfun_trait<FuncT>::arity << std::endl;
}

class TestTraits {
public:
	void funtest1(int)
	{

	}

	int funtest2(int, int)
	{
		return 0;
	}

	void Register()
	{
		RegisterFunction(this, &TestTraits::funtest1);
		RegisterFunction(this, &TestTraits::funtest2);
	}
};
///////////////////////////////////4///////////////////////////////////////

