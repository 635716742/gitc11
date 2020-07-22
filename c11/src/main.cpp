
#include "common.h"
#include "my_enable_if.h"
#include "algorithm.h"
#include "my_traits.h"
#include "SparseMatrix.h"
#include "threadpool.h"
#include "mforward.h"
#include "leetcode.h"

#define TEST_RANGE 8


int main()
{
	int sep = 1;

#if (TEST_RANGE == 1 || TEST_RANGE == -1)
	{
		std::cout << std::boolalpha;
		std::cout << std::is_base_of<MyTest::A, MyTest::B>::value << std::endl;
		std::cout << std::is_base_of<MyTest::B, MyTest::A>::value << std::endl;

		MyTest::A aa;
		MyTest::B bb;
		MyTest::C cc;
		MyTest::SetClass<MyTest::A>(&aa);
		MyTest::SetClass<MyTest::B>(&bb);

		//MyTest::SetClass<MyTest::C>(&cc); //error 没有返回值 enable_if false没有定义type

		my_algorithm my_aa;
		std::cout << "coin_max:" << my_aa.coin_max(7) << std::endl;
		//std::cout << "coin_max:" << my_aa.coin_max(7877) << std::endl;

		std::vector<int> next;

		my_aa.get_next("AAA", next);
		print_vec(next);
		my_aa.get_next("ABC", next);
		print_vec(next);
	}
#endif
#if (TEST_RANGE == 2 || TEST_RANGE == -1)
	{
		//ComponentConstructor<int > int_component;
		//int* obj_B = int_component.Create();
		//*obj_B = 10;
		//std::cout << "obj_B:" << *obj_B <<std::endl;

		//RMI_Wrapper 需要继承ObjAManager后Create才有意义
		ComponentConstructor<ObjAManager> component;
		ObjAManager* obj_A = component.Create();
		if (obj_A)
		{
			obj_A->print();
		}

		ObjAManager objB;
		objB.print();
		typedef std::vector<ObjAManager> VECTOR_INT;
		VECTOR_INT* vb = new VECTOR_INT;
		vb->push_back(objB);
		ObjAManager* ObjC = (ObjAManager*)vb;
		if (ObjC)
		{
			ObjC->print();
		}

		TestTraits tt;
		tt.Register();


		SparseMatrix tsm;
		Matrix matrix = { {1, 7, 0 ,0} ,{ 0, 7, 8 ,0 } ,{ 5, 0, 3 ,9 } ,{ 0, 6, 0 ,4 } };
		Matrix dst_matrix;
		CSRMatrix csmatrix;
		tsm.CSR(matrix, csmatrix);
		tsm.UnCSR(csmatrix, dst_matrix);
		print_vec(matrix);
		print_vec(dst_matrix);

	}
#endif
#if (TEST_RANGE == 3 ||TEST_RANGE == -1)
	{

		//std::thread t1([&]() {
		//	{
		//		//std::unique_lock<std::mutex> lock();
		//		int n = 10;
		//		for (int i = 0; i < n; ++i)
		//		{
		//			std::cout << " std::thread = " << i << std::endl;
		//		}
		//	}
		//});
		//std::cout << " main = " << 1000 << std::endl;
		//std::this_thread::sleep_for(std::chrono::seconds(2));
		//t1.join();

		//std::function<void()> fun1;
		//std::function<int()> fun2;
		//decltype(fun1) fun11;
	}
#endif
#if (TEST_RANGE == 4 ||TEST_RANGE == -1)
	{
		{
			//TestA aa;
			//std::vector<TestA> vec;
			//TestA bb = aa; //调用拷贝构造函数？？！！！！ 默认是浅拷贝
			//vec.push_back(aa);
		}
		int a = 15;
		int& b = a;
		const int& c = 15;

		int x = 150;
		int y = 250;
		const int & i = x + y;        //为右值 x + y命名常量别名 
		const int && ii = x + y;
		const int j = x + y;
		std::cout << &i << ":"<< &ii << std::endl;
		int* aa = &a;
		const int *caa = &a;
		mfoeward::func(&a);
		mfoeward::func(a);
		mfoeward::func(aa);
		mfoeward::func(caa);
	//	mfoeward::func(std::move(a));
	}
#endif
#if (TEST_RANGE == 5 ||TEST_RANGE == -1)
	sep = 1;
	{
		std::mutex main_lock;
		TestA aa;
		//TestA bb;
		//TestA cc = std::forward<TestA>(aa);   //dd cc的区别，cc多调用一次拷贝构造
		//TestA&& dd = std::move(aa);
		auto fun1 = std::bind(func, /*std::ref*/(aa)); //bind aa会调用拷贝构造  会导致bug(当参数是引用的话函数中做的修改并没有返回)
		//auto fun2 = std::make_shared<decltype(fun1)>(fun1);
		//std::make_shared<std::packaged_task<void()> >(fun1);
		std::packaged_task<void()> task(fun1);
		//auto future_result = task.get_future();
		//task();
		std::cout << "TestA = " << &aa << " " << aa.get_data() << " number = " << aa.get_num() <<std::endl;
		//std::cout << "TestB = " << &bb << " " << bb.get_data() << " number = " << bb.get_num() << std::endl;
		//print_separator(sep++);
		//func(aa);
		//fun1();
		//print_separator(sep++);
		//cthreadpool pool;
		//auto fun2 = pool.bind_simple(func, std::move(aa)); //bind aa会调用拷贝构造
		//fun2();
		print_separator(sep++);
		{
// 			std::lock_guard<std::mutex> lock(main_lock);
// 			auto result = pool.commit(func,/* std::ref*/(aa));
// 			if (result.valid())
// 			{
// 				result.get();
// 			}
		}
		//std::lock_guard<std::mutex> lock(main_lock);
		print_separator(sep++);
		std::cout << "TestA = " << &aa << " " << aa.get_data() << " number = " << aa.get_num() << std::endl;
		//std::cout << "TestB = " << &bb << " " << bb.get_data() << " number = " << bb.get_num() << std::endl;
	}
#endif
#if (TEST_RANGE == 6||TEST_RANGE == -1)
	{
		std::string str("123456789");
		std::string::size_type pos = str.find("0");
		if (pos != std::string::npos)
		{
			std::cout <<  std::numeric_limits<int>::max() <<" : string find" << std::endl;
			std::cout <<  std::numeric_limits<long>::max() <<" : string find" << std::endl;
		}
		else
		{
			std::cout << std::numeric_limits<unsigned int>::max() << ",string not find = "<< pos << std::endl;
			std::cout << std::numeric_limits<int>::max() << ",string not find = "<< pos << std::endl;
		}
	}
#endif
#if (TEST_RANGE == 7 ||TEST_RANGE == -1)
	{
		TestA aa;
		//std::string str("1231313131");
		std::vector<int> vec;
		for (int i = 0; i < 10000; ++i)
		{
			vec.push_back(i);
		}
		aa.print_offset();
		std::cout << sizeof(aa) << std::endl;
		std::cout << sizeof(TestA) << std::endl;
		std::cout << sizeof(std::string) << std::endl;
		std::cout << sizeof(std::vector<int>) << std::endl;
		std::cout << sizeof(vec) << std::endl;
		std::cout << sizeof(std::vector<std::string>) << std::endl;
		//std::cout << sizeof(str) << std::endl;
	}
	print_separator(sep++);
#endif
#if (TEST_RANGE == 8 ||TEST_RANGE == -1)
	{
		std::cout << std::boolalpha;
		int i = 0;
		for (auto var : LC::g_mastrix)
		{
			for (auto var1 : var)
			{
				std::cout << LC::leet_code4(LC::g_mastrix, var1) << ":" << ++i <<std::endl;
			}
		}
		//bool result = LC::leet_code4(LC::g_mastrix, 31);
		//std::cout << result << std::endl;
	}
	print_separator(sep++);
#endif
	getchar();
	return 0;
}