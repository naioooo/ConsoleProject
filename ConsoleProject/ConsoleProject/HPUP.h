#pragma once
#include "Item.h"
class HpUP :
    public Item
{
private:
    int m_HpUP;

public:
    HpUP();
    HpUP(const Point point, const int lifetime, const int HpUP);
    ~HpUP();

    int GetHpUP();

    void InsertBuffer(vector<string>& buffer) override;
    void Update(float elapsedTime) override;
};

