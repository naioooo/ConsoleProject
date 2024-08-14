#pragma once
#include "Object.h"
class Bullet : public Object
{
private:
	int m_speed;
	int m_dir;
	int m_damage;


public:
	Bullet();
	Bullet(const Point point, const int speed, const int dir, const int damage);
	~Bullet();

	void insertbuffer(vector<string>& buffer) override;
	void update(float elapsedTime) override;

	void move(float elapsedTime);
	bool collision_check(Point point) override;
};

