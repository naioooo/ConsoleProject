#pragma once
#include "Object.h"

class Character : public Object
{
protected:
	int m_HP;
	int m_speed;
	float m_speedCnt;

	int m_attack;
	int m_defense;

	int m_dir;

public:
	Character();
	Character(const Point point, const int HP, const int speed, const int attack, const int defense);
	~Character();

	int GetHP();
	int GetSpeed();
	int GetAttack();
	int GetDefense();

	void SetHP(int HP);

	virtual void InsertBuffer(vector<string>& buffer);
	virtual void Update(float elapsedTime);

	virtual void Move();
	virtual void Attack();

};

