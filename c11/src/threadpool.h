#pragma once
#include <queue>
#include <thread>
#include <atomic>
#include <future>
#include <condition_variable>
#include <functional>
#include <stdexcept>
#include "common.h"

#define THREAD_POOL_NUM 4
class cthreadpool
{
public:
	cthreadpool(unsigned short size = 4);
	virtual ~cthreadpool();
public:
	// �ύһ������
	// ����.get()��ȡ����ֵ��ȴ�����ִ����,��ȡ����ֵ
	// �����ַ�������ʵ�ֵ������Ա��
	// һ����ʹ��   bind�� .commit(std::bind(&Dog::sayHello, &dog));
	// һ������		mem_fn�� .commit(std::mem_fn(&Dog::sayHello), &dog)
	// Args���������õ�ʱ�����commitע���ʱ��ò�����std::ref(arg)���� ����õ�������
	template<class F, class... Args>
	auto commit(F&& f, Args&&... args) ->std::future<decltype(f(args...))>
	{
		int i = 100;
		print_separator(i++);
		if (stoped.load())
			throw std::runtime_error("commit on ThreadPool is stopped.");
		using RetType = decltype(f(args...)); // typename std::result_of<F(Args...)>::type, ���� f �ķ���ֵ����

		// bind�´������,�ᵼ��bug(�����������õĻ�����ֵ �᲻��)
		auto task = std::make_shared<std::packaged_task<RetType()> >(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);
		print_separator(i++);
		std::future<RetType> future = task->get_future();
		{
			std::lock_guard<std::mutex> lock( m_lock );
			tasks.emplace
			(
				[task]()
				{
					(*task)();
				}
			);
		}
		condition_var.notify_one(); // ����һ���߳�ִ��
		return future;
	}


public: //��߸�private   ת��ò�Ʋ���  ���ǻ��ε���copy����
	template <class F>
	class BindArgsMover {
	public:
		explicit BindArgsMover(F&& f) : f_(std::forward<F>(f)) {}

		template <class... Args>
		auto operator()(Args&&... args) {
			f_(std::move(args)...);
		}

	private:
		F f_;
	};

	template <class F, class... Args>
	auto bind_simple(F&& f, Args&&... args) {
		return std::bind(BindArgsMover<F>(std::forward<F>(f)),
			std::forward<Args>(args)...);
	}

private:
	using Task = std::function<void()>;
	std::vector<std::thread> pool;
	std::queue<Task> tasks;
	std::mutex m_lock;
	std::condition_variable condition_var;
	std::atomic<bool> stoped;
	std::atomic<int> free_num;
};

