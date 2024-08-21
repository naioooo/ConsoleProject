#pragma once
#include "Library.h"

class FrameRateManager {
public:
    FrameRateManager(int fps)
        : frameInterval_(std::chrono::milliseconds(1000 / fps)),
        lastTick_(std::chrono::steady_clock::now()) {}

    bool tick(float& elapsedTime) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = now - lastTick_;

        // 경과 시간을 milliseconds로 변환한 후 float형으로 변환합니다.
        elapsedTime = std::chrono::duration<float, std::milli>(elapsed).count();

        if (elapsed >= frameInterval_) {
            lastTick_ = now; // 마지막 tick 시간을 업데이트합니다.
            return true; // 프레임을 찍었다는 것을 알립니다.
        }

        return false; // 아직 프레임 시간 간격이 지나지 않았습니다.
    }

private:
    std::chrono::milliseconds frameInterval_;
    std::chrono::steady_clock::time_point lastTick_;
};
