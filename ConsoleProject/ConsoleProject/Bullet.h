#pragma once
#include "Object.h"
class Bullet : public Object
{
private:
	float m_speed_cnt;
	int m_dir;
	int m_damage;

	int m_lifetime;


public:
	Bullet();
	Bullet(const Point point, const int speed, const int dir, const int damage, const int lifetime);
	~Bullet();

	void insertbuffer(vector<string>& buffer) override;
	void update(float elapsedTime) override;

	void move(float elapsedTime);
	bool collision_check(Point point) override;
};

