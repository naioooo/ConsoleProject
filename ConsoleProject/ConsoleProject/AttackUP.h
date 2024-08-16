#pragma once
#include "Item.h"
class AttackUP : public Item
{
private:
    int m_AttackUP;

public:
    AttackUP();
    AttackUP(const Point point, const int lifetime, const int AttackUP);
    ~AttackUP();

    int getAttackUP();

    void insertbuffer(vector<string>& buffer) override;
    void update(float elapsedTime) override;
};

