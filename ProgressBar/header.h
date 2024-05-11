#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <Windows.h>

#define ESC "\033"
#define CSI "["
#define PREVIOUS_LINE "F"

const int THREAD_COUNT = 3;
const int TOTAL_PROGRESS = 40;

std::chrono::steady_clock::time_point timers[THREAD_COUNT][2];

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

enum ErrorType {
    NO,
    NORMAL,
    MEAN,
    CRITICAL
};

struct threadInfo {
    int countToVal;
    int progress;
    std::thread thread;
    bool barDone;
    ErrorType error;
};