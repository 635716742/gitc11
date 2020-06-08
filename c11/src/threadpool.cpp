#include "threadpool.h"



cthreadpool::cthreadpool(unsigned short size)
	:stoped(false)
{
	free_num = size < 1 ? 1 : size;
	for (size = 0; size < free_num; ++size)
	{
		pool.emplace_back(
			[this]
			{
				while (!this->stoped)
				{
					Task task;
					{
						std::unique_lock<std::mutex> lock(this->m_lock);
						this->condition_var.wait(lock,
							[this] 
							{
								return this->stoped.load() || !this->tasks.empty();
							}
						); //wait第二个参数为false才会wait，第二个参数为true才会被唤醒;
						if (this->tasks.empty()&& this->stoped)
							return;
						task = std::move(this->tasks.front());
						this->tasks.pop();
					}
					free_num--;
					task();
					free_num++;
				}
			}
		);
	}
}


cthreadpool::~cthreadpool()
{
	stoped.store(true);
	condition_var.notify_all(); // 唤醒所有线程执行
	for (std::thread& thread : pool) {
	//thread.detach(); // 让线程“自生自灭”
	if (thread.joinable())
		thread.join(); // 等待任务结束， 前提：线程一定会执行完
	}
}
