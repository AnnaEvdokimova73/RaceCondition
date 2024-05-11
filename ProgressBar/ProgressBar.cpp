#include "header.h"

void setError(threadInfo& tInfo)
{
    // имитация ошибки
    if (tInfo.progress == 20)
    {
        tInfo.error = NORMAL;
    }
    /*else
    {
        tInfo.error = NO;
    }*/

    // имитация ошибок
    /*if (tInfo.progress % 10 == 0 || tInfo.progress % 95 == 0)
    {
        tInfo.error = NORMAL;
    }
    else if (tInfo.progress % 13 == 0 || tInfo.progress % 55 == 0)
    {
        tInfo.error = MEAN;
    }
    else if (tInfo.progress % 24 == 0 || tInfo.progress % 37 == 0)
    {
        tInfo.error = CRITICAL;
    }
    else
    {
        tInfo.error = NO;
    }*/
}

bool setNewColor(int i, int progress, ErrorType error)
{
    if (i == 10)
    {
        switch (error)
        {
        case NO:
            SetConsoleTextAttribute(h, 15);
            return false;
            break;
        case NORMAL:
            SetConsoleTextAttribute(h, 2);
            return true;
            break;
        case MEAN:
            SetConsoleTextAttribute(h, 14);
            return true;
            break;
        case CRITICAL:
            SetConsoleTextAttribute(h, 4);
            return true;
            break;
        }
    }
    return false;
}

void setProgress(threadInfo& tInfo, int num)
{
    int ran = 1;
    for (tInfo.progress = 0; tInfo.progress < tInfo.countToVal; tInfo.progress += ran)
    {
        ran = rand() % 3;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100));

        setError(tInfo);
    }
}

void updateBar(threadInfo& tInfo, int num)
{
    if (!tInfo.barDone)
    {
        std::cout << num << " " << tInfo.thread.get_id() << " ";

        int numChars = (tInfo.progress * 100 / tInfo.countToVal) *
            TOTAL_PROGRESS / 100;

        std::cout << "[";
        for (int i = 0; i < numChars; ++i)
        {
            if (setNewColor(i, tInfo.progress, tInfo.error))
            {
                // tInfo.error = NO;
            }
            std::cout << "-";

            SetConsoleTextAttribute(h, 15);
        }
        //tInfo.error = NO;

        for (int i = 0; i < TOTAL_PROGRESS - numChars; ++i)
        {
            std::cout << " ";
        }
        std::cout << "]";

        if (TOTAL_PROGRESS - numChars <= 0)
        {
            tInfo.barDone = true;
        }

        timers[num][1] = std::chrono::steady_clock::now(); // время окончания перерисовки
        std::chrono::duration<double> dur = (timers[0][0] - timers[num][1]);
        std::cout << " " << dur.count() << "s";
    }
    std::cout << "\n";
}

int main()
{
    threadInfo threads[THREAD_COUNT];

    std::cout << "#    ";
    std::cout << "id\t\t\t";
    std::cout << "Progress Bar\t\t\t";
    std::cout << "Time\n";
    
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        threads[i].countToVal = rand() % 100;
        threads[i].progress = 0;
        threads[i].barDone = false;
        threads[i].error = NO;
        threads[i].thread = std::thread(setProgress, std::ref(threads[i]), i);
    }

    timers[0][0] = std::chrono::steady_clock::now(); // время начала одинаковое
    bool done = false;
    while (!done)
    {
        done = true;
        for (int i = 0; i < THREAD_COUNT; ++i)
        {
            updateBar(threads[i], i);
            
            if (threads[i].progress < threads[i].countToVal)
            {
                threads[i].barDone = false;
                done = false;
            }
        }
        if (!done)
        {
            std::cout << ESC << CSI << THREAD_COUNT << PREVIOUS_LINE;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        threads[i].thread.join();
    }
}