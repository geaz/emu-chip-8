#include <chrono>

#include "clock.h"

void Clock::Reset()
{
    lastCycleChip = -1;
    lastCycleTimer = -1;
}

int Clock::CatchUpChipCycles(int frequency)
{
    auto now = std::chrono::system_clock::now();
    long long currentClockMs = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count();

    if(lastCycleChip == -1) lastCycleChip = currentClockMs;
    int cycles = (int) (currentClockMs - lastCycleChip) * frequency / 1000;
    if(cycles > 0) lastCycleChip = currentClockMs;
    return cycles;
}

int Clock::CatchUpTimerCycles(int frequency)
{
    auto now = std::chrono::system_clock::now();
    long long currentClockMs = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count();

    if(lastCycleTimer == -1) lastCycleTimer = currentClockMs;
    int cycles = (int) (currentClockMs - lastCycleTimer) * frequency / 1000;
    if(cycles > 0) lastCycleTimer = currentClockMs;
    return cycles;
}