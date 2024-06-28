#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>

template<typename T>
class ConditionVar_Concurrent_Queue
{
private:
	std::mutex mx;
	std::queue<T> queue;
	std::condition_variable condition;
public:
	ConditionVar_Concurrent_Queue() = default;

	void push(T element)
	{
		std::lock_guard<std::mutex> lg{ mx };
		queue.push(element);
		condition.notify_one();
	}

	void pop(T& element)
	{
		std::unique_lock<std::mutex> lg{ mx };
		condition.wait(lg, [this] { return !queue.empty(); });
		element = queue.front();
		queue.pop();
	}

	size_t size()
	{
		std::lock_guard<std::mutex> lg{ mx };
		return queue.size();
	}
};


