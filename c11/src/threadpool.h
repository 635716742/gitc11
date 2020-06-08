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
	// 提交一个任务
	// 调用.get()获取返回值会等待任务执行完,获取返回值
	// 有两种方法可以实现调用类成员，
	// 一种是使用   bind： .commit(std::bind(&Dog::sayHello, &dog));
	// 一种是用		mem_fn： .commit(std::mem_fn(&Dog::sayHello), &dog)
	// Args参数是引用的时候调用commit注册的时候该参数用std::ref(arg)包含 表调用的是引用
	template<class F, class... Args>
	auto commit(F&& f, Args&&... args) ->std::future<decltype(f(args...))>
	{
		int i = 100;
		print_separator(i++);
		if (stoped.load())
			throw std::runtime_error("commit on ThreadPool is stopped.");
		using RetType = decltype(f(args...)); // typename std::result_of<F(Args...)>::type, 函数 f 的返回值类型

		// bind会拷贝参数,会导致bug(当参数是引用的话返回值 会不对)
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
		condition_var.notify_one(); // 唤醒一个线程执行
		return future;
	}


public: //后边改private   转发貌似不行  还是会多次调用copy函数
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

