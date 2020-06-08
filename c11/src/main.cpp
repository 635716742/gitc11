
#include "common.h"
#include "my_enable_if.h"
#include "algorithm.h"
#include "my_traits.h"
#include "SparseMatrix.h"
#include "threadpool.h"

int main()
{
	int sep = 1;
	{
		std::cout << std::boolalpha;
		std::cout << std::is_base_of<MyTest::A, MyTest::B>::value << std::endl;
		std::cout << std::is_base_of<MyTest::B, MyTest::A>::value << std::endl;

		MyTest::A aa;
		MyTest::B bb;
		MyTest::C cc;
		MyTest::SetClass<MyTest::A>(&aa);
		MyTest::SetClass<MyTest::B>(&bb);

		//MyTest::SetClass<MyTest::C>(&cc); //error û�з���ֵ enable_if falseû�ж���type

		my_algorithm my_aa;
		std::cout << "coin_max:" << my_aa.coin_max(7) << std::endl;
		//std::cout << "coin_max:" << my_aa.coin_max(7877) << std::endl;

		std::vector<int> next;

		my_aa.get_next("AAA", next);
		print_vec(next);
		my_aa.get_next("ABC", next);
		print_vec(next);
	}

	{
		//ComponentConstructor<int > int_component;
		//int* obj_B = int_component.Create();
		//*obj_B = 10;
		//std::cout << "obj_B:" << *obj_B <<std::endl;

		//RMI_Wrapper ��Ҫ�̳�ObjAManager��Create��������
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

	{
		{
			//TestA aa;
			//std::vector<TestA> vec;
			//TestA bb = aa; //���ÿ������캯�������������� Ĭ����ǳ����
			//vec.push_back(aa);
		}
		int a = 15;
		int& b = a;
		const int& c = 15;

		int x = 150;
		int y = 250;
		const int & i = x + y;        //Ϊ��ֵ x + y������������ 
		const int && ii = x + y;
		const int j = x + y;
		std::cout << &i << ":"<< &ii << std::endl;
	}
	sep = 1;
	{
		std::mutex main_lock;
		TestA aa;
		TestA bb;
		//TestA cc = std::move(aa);   //bb cc������cc�����һ�ο�������
		//TestA&& bb = std::move(aa);
		auto fun1 = std::bind(func, std::ref(aa)); //bind aa����ÿ�������  �ᵼ��bug(�����������õĻ������������޸Ĳ�û�з���)
		std::packaged_task<void()> task(fun1);
		auto future_result = task.get_future();
		task();
		std::cout << "TestA = " << &aa << " " << aa.get_data() << " number = " << aa.get_num() <<std::endl;
		std::cout << "TestB = " << &bb << " " << bb.get_data() << " number = " << bb.get_num() << std::endl;
		//print_separator(sep++);
		//func(aa);
		//fun1();
		//print_separator(sep++);
		cthreadpool pool;
		//auto fun2 = pool.bind_simple(func, std::move(aa)); //bind aa����ÿ�������
		////fun2();

		//print_separator(sep++);
		//{
		//	std::lock_guard<std::mutex> lock(main_lock);
		//	auto result = pool.commit(func, /*std::ref*/(bb));
		//	result.get();
		//}
		//std::lock_guard<std::mutex> lock(main_lock);
		print_separator(sep++);
		std::cout << "TestA = " << &aa << " " << aa.get_data() << " number = " << aa.get_num() << std::endl;
		std::cout << "TestB = " << &bb << " " << bb.get_data() << " number = " << bb.get_num() << std::endl;
	}
	print_separator(sep++);
	getchar();
	return 0;
}