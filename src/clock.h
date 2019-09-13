#pragma once
#ifndef CLOCK_H
#define CLOCK_H

class Clock
{
    public:
        void Reset();
        int CatchUpChipCycles(int frequency);
        int CatchUpTimerCycles(int frequency);

    private:
        long long lastCycleTimer = -1;
        long long lastCycleChip = -1;
};

#endif // CLOCK_H