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
						); //wait�ڶ�������Ϊfalse�Ż�wait���ڶ�������Ϊtrue�Żᱻ����;
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
	condition_var.notify_all(); // ���������߳�ִ��
	for (std::thread& thread : pool) {
	//thread.detach(); // ���̡߳���������
	if (thread.joinable())
		thread.join(); // �ȴ���������� ǰ�᣺�߳�һ����ִ����
	}
}
