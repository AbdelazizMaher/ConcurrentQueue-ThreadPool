#pragma once

#include <vector>
#include <thread>
#include <functional>
#include "ConditionVar_Concurrent_Queue.h"

using Func = std::function<void()>;

class ThreadPool
{
private:
	std::vector<std::thread> m_threadPool;
	ConditionVar_Concurrent_Queue<Func> m_queue;
	void taskExecuter();
public:
	ThreadPool();
	~ThreadPool();

	void submitTasks(Func task);
};

