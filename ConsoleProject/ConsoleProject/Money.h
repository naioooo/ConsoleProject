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

    int getmoney();

    void insertbuffer(vector<string>& buffer) override;
    void update(float elapsedTime) override;
};

