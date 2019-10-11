#include <chrono>

#include "clock.hpp"

void Clock::Reset()
{
    lastCycleChip = -1;
    lastCycleTimer = -1;
}

int Clock::CatchUpCycles(int frequency,  TimerType timerType)
{
    auto now = std::chrono::system_clock::now();
    long long currentClockMs = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count();

    long long* lastTimer = timerType == CHIP
        ? &lastCycleChip
        : &lastCycleTimer;

    if(*lastTimer == -1) *lastTimer = currentClockMs;
    int cycles = (int) (currentClockMs - *lastTimer) * frequency / 1000;
    if(cycles > 0) *lastTimer = currentClockMs;
    return cycles;
}