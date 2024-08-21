#include "TimeManager.h"

FrameRateManager::FrameRateManager(int fps) : m_frameInterval(std::chrono::milliseconds(1000 / fps)), m_lastTick(std::chrono::steady_clock::now())
{
}

bool FrameRateManager::Tick(float& elapsedTime)
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = now - m_lastTick;

    // ��� �ð��� milliseconds�� ��ȯ�� �� float������ ��ȯ�մϴ�.
    elapsedTime = std::chrono::duration<float, std::milli>(elapsed).count();

    if (elapsed >= m_frameInterval) 
    {
        m_lastTick = now; // ������ tick �ð��� ������Ʈ�մϴ�.
        return true; // �������� ����ٴ� ���� �˸��ϴ�.
    }

    return false; // ���� ������ �ð� ������ ������ �ʾҽ��ϴ�.
}
