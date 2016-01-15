#ifndef TIMER_H
#define TIMER_H

#ifdef _WIN32

#include "windows.h"

namespace WindowsTimer
{
LARGE_INTEGER frequency;
LARGE_INTEGER t1, t2;
double elapsedTime;

void tic()
{
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&t1);
}

void tac()
{
    QueryPerformanceCounter(&t2);
    elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
    cout << elapsedTime << " ms.\n";
}
}

#endif //_WIN32

#endif // TIMER_H
