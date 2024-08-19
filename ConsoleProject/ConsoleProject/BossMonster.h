#pragma once
#include "Monster.h"
#include "FireBall.h"


class BossMonster : public Monster
{
private:
	vector<shared_ptr<FireBall>> m_fireball;

public:
	BossMonster();
	BossMonster(const Point point, const int HP, const int speed, const int attack, const int defense);
	~BossMonster();

	void InsertBuffer(vector<string>& buffer) override;
	void Update(float elapsedTime) override;
	bool IsValidPoint(Point point) override;

	void ExplosiveFireBall(int width, int height);
	void MeteorFireBall();

};

