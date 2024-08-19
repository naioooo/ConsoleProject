#pragma once
#include "Item.h"
class Money :
    public Item
{
private:
    int m_money;

public:
    Money(); 
    Money(const Point point, const int lifetime, const int money);
    ~Money();

    int GetMoney();

    void InsertBuffer(vector<string>& buffer) override;
    void Update(float elapsedTime) override;
};

