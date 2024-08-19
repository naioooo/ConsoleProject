#pragma once
#include "Object.h"
class FireBall : public Object
{
private:
	float m_speedCnt;
	int m_dir;
	int m_damage;

	int m_lifetime;
	int m_lifetimeCnt;


public:
	FireBall();
	FireBall(const Point point, const int speed, const int dir, const int damage, const int lifetime);
	~FireBall();

	void InsertBuffer(vector<string>& buffer) override;
	void Update(float elapsedTime) override;

	void Move(float elapsedTime);
	bool CollisionCheck(Point point) override;
};

