#pragma once
#include "Object.h"

class Character : public Object
{
protected:
	int m_HP;
	int m_speed;

	int m_attack;
	int m_defense;


public:
	Character();
	Character(const Point point, const int HP, const int speed, const int attack, const int defense);
	~Character();

	int getHP();
	int getspeed();
	int getattack();
	int getdefense();

	virtual void draw();
	virtual void move();
	virtual void attack();
	virtual void update();

};

