#pragma once
#ifndef CLOCK_H
#define CLOCK_H

enum TimerType { CHIP, TIMER };

class Clock
{
    public:
        void Reset();
        int CatchUpCycles(int frequency,  TimerType timerType);

    private:
        long long lastCycleTimer = -1;
        long long lastCycleChip = -1;
};

#endif // CLOCK_H