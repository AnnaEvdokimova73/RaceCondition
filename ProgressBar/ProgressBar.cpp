#include <iostream>
#include <thread>

void count()
{
    system("color 0A");
    std::cout << "\n";
    std::cout << std::this_thread::get_id << "\t";
    // Print initial loading bar 
    char a = 177, b = 219;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));


    // Print loading bar progress 
    for (int i = 0; i < 26; i++) {
        std::cout << "[";

        // Sleep for 1 second 
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void count1()
{
    system("color 0A");
    std::cout << "\n";
    std::cout << std::this_thread::get_id << "\t";
    // Print initial loading bar 
    char a = 177, b = 219;


    for (int i = 0; i < 26; i++) {
        printf("%c", b);
        // Sleep for 1 second 
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main()
{
    std::cout << "Hello World!\n";
    std::thread t1(count1);
    std::thread t2(count);

    t1.join();
    t2.join();
}