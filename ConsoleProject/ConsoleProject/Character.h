#pragma once
#include "Object.h"

class Character : public Object
{
protected:
	int m_HP;
	int m_speed;

	int m_attack;
	int m_defense;

	int m_dir;

public:
	Character();
	Character(const Point point, const int HP, const int speed, const int attack, const int defense);
	~Character();

	int getHP();
	int getspeed();
	int getattack();
	int getdefense();

	virtual void insertbuffer(vector<string>& buffer);
	virtual void update();

	virtual void move();
	virtual void attack();

};

