#pragma once
#include "Item.h"
class AttackUP : public Item
{
private:
    int m_AttackUP;

public:
    AttackUP();
    AttackUP(const Point point, const int lifetime, const int attackUP);
    ~AttackUP();

    int GetAttackUP();

    void InsertBuffer(vector<string>& buffer) override;
    void Update(float elapsedTime) override;
};

