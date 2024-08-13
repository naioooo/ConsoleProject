#pragma once
#include "Character.h"

class Player :
	public Character
{
private:
	string m_name;


public:
	Player();
	Player(const Point point, const int HP, const int speed, const int attack, const int defense, const string& name);
	~Player();

	void insertbuffer(vector<string>& buffer) override;
	void update() override;

	void move() override;
	void attack() override;
	bool collision_check(Point point) override;
};

