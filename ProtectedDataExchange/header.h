#pragma once

#include <iostream>
#include <list>
#include <mutex>
#include <thread>

enum NamespaceType
{
    LOCK,
    SCOPED_LOCK,
    UNIQUE_LOCK
};

class Data
{
public:
    Data(int _a = 0, double _b = 0) : a{ _a }, b{ _b }
    {}

    /*void swap(Data& data2)
    {
        dataMutex.lock();
        data2.dataMutex.lock();

        Data temp;
        temp.a = data2.a;
        temp.b = data2.b;

        data2.a = a;
        data2.b = b;

        a = temp.a;
        b = temp.b;

        dataMutex.unlock();
        data2.dataMutex.unlock();
    }*/

public:
    int a;
    double b;
    std::mutex dataMutex;
};

Data data(50, 6.7);
Data data2(39, 12.9);
Data data3(24, 0.73);
