#pragma once
#include "Item.h"
class SpeedUP :
    public Item
{
private:
    int m_speedUP;

public:
    SpeedUP();
    SpeedUP(const Point point, const int lifetime, const int speedUP);
    ~SpeedUP();

    int GetSpeedUP();

    void InsertBuffer(vector<string>& buffer) override;
    void Update(float elapsedTime) override;
};

