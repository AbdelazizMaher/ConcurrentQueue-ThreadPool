#pragma once

#include <mutex>
#include <queue>

class Concurrent_Queue_exception : public std::runtime_error
{
public:
	Concurrent_Queue_exception() : std::runtime_error("Queue is empty") { }
	Concurrent_Queue_exception(const char* s) : std::runtime_error(s) { }
};

template<typename T>
class Concurrent_Queue
{
private:
	std::mutex mx;
	std::queue<T> queue;
public:
	Concurrent_Queue() = default;

	void push(T element)
	{
		std::lock_guard<std::mutex> lg{ mx };
		queue.push(element);
	}

	void pop(T& element)
	{
		std::unique_lock<std::mutex> lg{ mx };
		if (queue.empty())
			throw Concurrent_Queue_exception("[ERORR]: Queue is empty");
		element = queue.front();
		queue.pop();
	}

	size_t size()
	{
		std::lock_guard<std::mutex> lg{ mx };
		return queue.size();
	}
};


