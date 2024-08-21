#include "SpeedUP.h"

SpeedUP::SpeedUP()
{
}

SpeedUP::SpeedUP(const Point point, const int lifetime, const int speedUP)
    : Item(point, lifetime), m_speedUP(speedUP)
{
    m_name = "S";
}

SpeedUP::~SpeedUP()
{
}

int SpeedUP::GetSpeedUP() const
{
    return m_speedUP;
}

void SpeedUP::InsertBuffer(vector<string>& buffer)
{
    buffer[m_point.y][m_point.x] = CH_SPEEDUP;
}

void SpeedUP::Update(float elapsedTime)
{
    Item::Update(elapsedTime);
}
