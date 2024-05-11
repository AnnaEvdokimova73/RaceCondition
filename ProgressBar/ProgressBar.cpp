#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

const int THREAD_COUNT = 5;
const int TOTAL_PROGRESS = 10;

std::mutex mtx;

void count(int id)
{
    system("color 0A");
    std::cout << "\n";
    std::cout << id << "\t";
    std::cout << std::this_thread::get_id << "\t";
    std::lock_guard<std::mutex> lock(mtx);

    for (int i = 0; i < TOTAL_PROGRESS; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "|";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

int main()
{
    std::thread threads[THREAD_COUNT];
    
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        threads[i] = std::thread(count, i);
    }

    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        threads[i].join();
    }
}