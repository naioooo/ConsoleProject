#pragma once
#include "Projectile.h"
class Bullet : public Projectile
{
private:

public:
	Bullet();
	Bullet(const Point point, const int speed, const int dir, const int damage, const int lifetime);
	~Bullet();

	void InsertBuffer(vector<string>& buffer) override;
	bool CollisionCheck(Point point) override;
};

