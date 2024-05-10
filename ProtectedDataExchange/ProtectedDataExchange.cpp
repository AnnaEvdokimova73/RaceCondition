#include "header.h"

namespace exchange_lock
{
    void swap(Data& data1, Data& data2)
    {
        data1.dataMutex.lock();
        data2.dataMutex.lock();

        Data temp;
        temp.a = data2.a;
        temp.b = data2.b;

        data2.a = data1.a;
        data2.b = data1.b;

        data1.a = temp.a;
        data1.b = temp.b;

        data1.dataMutex.unlock();
        data2.dataMutex.unlock();
    }
}

namespace exchange_scoped_lock
{
    void swap(Data& data1, Data& data2)
    {
        std::scoped_lock mutexScopedLock(data1.dataMutex, data2.dataMutex);

        Data temp;
        temp.a = data2.a;
        temp.b = data2.b;

        data2.a = data1.a;
        data2.b = data1.b;

        data1.a = temp.a;
        data1.b = temp.b;
    }
}

namespace exchange_unique_lock
{
    void swap(Data& data1, Data& data2)
    {
        std::unique_lock uniqLock1(data1.dataMutex);
        std::unique_lock uniqLock2(data2.dataMutex);

        Data temp;
        temp.a = data2.a;
        temp.b = data2.b;

        data2.a = data1.a;
        data2.b = data1.b;

        data1.a = temp.a;
        data1.b = temp.b;
    }
}

template <typename T>
void printInfo(const std::string& title, T& data1, T& data2, T& data3)
{
    std::cout << title;
    std::cout << "Data1 {a, b}: " << data1.a << "  " << data1.b << std::endl;
    std::cout << "Data2 {a, b}: " << data2.a << "  " << data2.b << std::endl;
    std::cout << "Data3 {a, b}: " << data3.a << "  " << data3.b << std::endl;
}

void exchangeData(int namespaceType, const std::string& title)
{
    void (*swap)(Data & data1, Data & data2); // объявление swap, как указателя на функцию

    switch (namespaceType)
    {
    case NamespaceType::LOCK:
        swap = exchange_lock::swap;
        break;
    case NamespaceType::SCOPED_LOCK:
        swap = exchange_scoped_lock::swap;
        break;
    case NamespaceType::UNIQUE_LOCK:
        swap = exchange_unique_lock::swap;
        break;
    default:
        return;
    }

    std::thread firstTread(swap, std::ref(data), std::ref(data2));
    std::thread secTread(swap, std::ref(data2), std::ref(data));

    firstTread.join();
    secTread.join();

    printInfo(title, data, data2, data3);
}

int main()
{
    std::list<std::string> titleList;
    titleList.push_back("Using lock/unock\n");
    titleList.push_back("Using std::scoped_lock\n");
    titleList.push_back("Using std::unique_lock\n");

    int c = 0; // счетчик NamespaceType
    for (auto title : titleList)
    {
        exchangeData(NamespaceType(c++), title);
        std::cout << "\n";
    }

}
