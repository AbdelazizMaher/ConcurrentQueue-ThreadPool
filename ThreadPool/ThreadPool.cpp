#include "ThreadPool.h"

ThreadPool::ThreadPool()
{
	auto core_count = std::thread::hardware_concurrency();
	for (size_t i = 0; i < core_count; i++)
		m_threadPool.push_back(std::thread{ &ThreadPool::taskExecuter, this });
}

ThreadPool::~ThreadPool()
{
	for (auto& thread : m_threadPool)
		thread.join();
}

void ThreadPool::taskExecuter()
{
	while (true)
	{
		Func task;
		m_queue.pop(task);
		task();
	}
}

void ThreadPool::submitTasks(Func task)
{
	m_queue.push(task);
}
