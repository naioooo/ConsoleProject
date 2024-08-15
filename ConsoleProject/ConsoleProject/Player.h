#pragma once
#include "Character.h"
#include "Bullet.h"

class Player :
	public Character
{
private:
	string m_name;
	vector<shared_ptr<Bullet>> m_bullets;
	unsigned int m_money;


public:
	Player();
	Player(const Point point, const int HP, const int speed, const int attack, const int defense, const string& name);
	~Player();

	void insertbuffer(vector<string>& buffer) override;
	void update(float elapsedTime) override;

	unsigned int getmoney();
	void setmoney(const unsigned int money);

	void input();
	void move() override;
	void attack() override;
	bool collision_check(Point point) override;
};

