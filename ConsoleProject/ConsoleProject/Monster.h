#pragma once
#include "Character.h"
class Monster :
    public Character
{
private:


public:
	Monster();
	Monster(const Point point, const int HP, const int speed, const int attack, const int defense);
	~Monster();

	void move(const DIR dir);
	void attack();
	void update();
	void insertbuffer(vector<string>& buffer);
};

