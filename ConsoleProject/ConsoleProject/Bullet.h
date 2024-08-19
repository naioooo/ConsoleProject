#pragma once
#include "Object.h"
class Bullet : public Object
{
private:
	float m_speedCnt;
	int m_dir;
	int m_damage;

	int m_lifetime;
	int m_lifetimeCnt;


public:
	Bullet();
	Bullet(const Point point, const int speed, const int dir, const int damage, const int lifetime);
	~Bullet();

	void InsertBuffer(vector<string>& buffer) override;
	void Update(float elapsedTime) override;

	void Move(float elapsedTime);
	bool CollisionCheck(Point point) override;
};

