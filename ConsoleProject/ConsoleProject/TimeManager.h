#pragma once
#include "Library.h"

class FrameRateManager
{
private:
    std::chrono::milliseconds m_frameInterval;
    std::chrono::steady_clock::time_point m_lastTick;

public:
    FrameRateManager(int fps);
    bool Tick(float& elapsedTime);
};
