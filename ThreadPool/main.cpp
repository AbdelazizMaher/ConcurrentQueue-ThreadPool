#include <iostream>
#include <mutex>
#include "ThreadPool.h"

std::mutex mx;
using namespace std::chrono_literals;

void task()
{
	std::lock_guard<std::mutex> lg{ mx };

	std::cout << "Thread ID : " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(100ms);
	std::cout << "Thread ID : " << std::this_thread::get_id() << std::endl;
}

int main()
{
	std::cout << "Creating a thread pool with " << std::thread::hardware_concurrency() << " Threads" << std::endl;

	ThreadPool pool;

	for (size_t i = 0; i < 20; i++)
		pool.submitTasks(task);

	std::this_thread::sleep_for(2s);

	return 0;
}