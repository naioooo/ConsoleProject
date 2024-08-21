#pragma once
#include "Object.h"
class Projectile : public Object
{
protected:
	float m_speed;
	float m_speedCnt;

	int m_lifetime;
	int m_lifetimeCnt;

	int m_dir;
	int m_damage;

public:
	Projectile();
	Projectile(const Point point, const int speed, const int dir, const int damage, const int lifetime);
	~Projectile();

	void Update(float elapsedTime) override;
	void Move(float elapsedTime);
};

