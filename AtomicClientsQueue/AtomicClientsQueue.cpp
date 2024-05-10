#include <iostream>
#include <atomic>
#include <thread>

//load - считывания
//store - запись

const unsigned int maxClientCount = 10;

void clientIncrease(std::atomic<unsigned int>& clientCount)
{
    while (clientCount < maxClientCount)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // задержка на 1 сек
        clientCount.store(clientCount.load(std::memory_order_seq_cst) + 1,
                          std::memory_order_seq_cst);
        // clientCount.store(clientCount.load(std::memory_order_relaxed) + 1,
        //                   std::memory_order_relaxed);
        std::cout << "Client added. Total clients number:\t" << clientCount << std::endl;
    }
}

void clientDecrease(std::atomic<unsigned int>& clientCount)
{
    while (clientCount > 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // задержка на 2 сек
        clientCount.store(clientCount.load(std::memory_order_seq_cst) - 1,
                          std::memory_order_seq_cst);
        // clientCount.store(clientCount.load(std::memory_order_relaxed) - 1,
        //                   std::memory_order_relaxed);
        std::cout << "Client deleted. Total clients number:\t" << clientCount << std::endl;
    }
}

int main()
{
    std::atomic<unsigned int> clientCount{ 2 };
    std::cout << "Total clients number at the beginning:\t" << clientCount << std::endl;

    std::thread clientTread(clientIncrease, std::ref(clientCount));
    std::thread operTread(clientDecrease, std::ref(clientCount));

    clientTread.join();
    operTread.join();

    std::cout << "Total clients number at the end:\t" << clientCount << std::endl;
    return 0;
}

