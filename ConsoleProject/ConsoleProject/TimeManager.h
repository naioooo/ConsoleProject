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

        // ��� �ð��� milliseconds�� ��ȯ�� �� float������ ��ȯ�մϴ�.
        elapsedTime = std::chrono::duration<float, std::milli>(elapsed).count();

        if (elapsed >= frameInterval_) {
            lastTick_ = now; // ������ tick �ð��� ������Ʈ�մϴ�.
            return true; // �������� ����ٴ� ���� �˸��ϴ�.
        }

        return false; // ���� ������ �ð� ������ ������ �ʾҽ��ϴ�.
    }

private:
    std::chrono::milliseconds frameInterval_;
    std::chrono::steady_clock::time_point lastTick_;
};
