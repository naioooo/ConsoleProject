#pragma once
#include "Projectile.h"
class FireBall : public Projectile
{
private:

public:
	FireBall();
	FireBall(const Point point, const int speed, const int dir, const int damage, const int lifetime);
	~FireBall();

	void InsertBuffer(vector<string>& buffer) override;
	bool CollisionCheck(Point point) override;
};

