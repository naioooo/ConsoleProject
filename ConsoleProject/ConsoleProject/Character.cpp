#pragma once
#include "Character.h"

Character::Character()
{

}

Character::Character(const Point point, const int HP, const int speed, const int attack, const int defense)
	: Object(point), m_HP(HP), m_speed(speed), m_attack(attack), m_defense(defense), m_dir(0)
{
}

Character::~Character()
{
}

int Character::GetHP() const
{
	return m_HP;
}

int Character::GetSpeed() const
{
	return m_speed;
}

int Character::GetAttack() const
{
	return m_attack;
}

int Character::GetDefense() const
{
	return m_defense;
}

void Character::SetHP(int HP)
{
	m_HP = HP;
	if (m_HP <= 0)
	{
		SetAlive(false);
	}
}

void Character::SetSpeed(int speed)
{
	m_speed = speed;
}

void Character::SetDir(int dir)
{
	m_dir = dir;
}

void Character::InsertBuffer(vector<string>& buffer)
{
}

void Character::Update(float elapsedTime)
{
}

void Character::Move()
{
}

void Character::Attack()
{
}

