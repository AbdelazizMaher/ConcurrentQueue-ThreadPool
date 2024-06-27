#include <iostream>
#include <future>
#include "Concurrent_Queue.h"

Concurrent_Queue<std::string> conc_queue;

using namespace std::chrono_literals;

void Consumer()
{
    std::string data{};

    try {
        std::cout << "Consumer calling pop..." << std::endl;
        conc_queue.pop(data);
        std::cout << "Consumer received data..." << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Exception caught:" << e.what() << std::endl;
    }
}

void Producer()
{
    std::string data{"push data"};

    std::cout << "Producer calling push..." << std::endl;
    conc_queue.push(data);
    std::cout << "Producer pushed data..." << std::endl;
}

int main() {
    auto p = std::async(std::launch::async, Producer);
    std::this_thread::sleep_for(1s);
    auto c = std::async(std::launch::async, Consumer);

    p.wait();
    c.wait();

    return 0;
}