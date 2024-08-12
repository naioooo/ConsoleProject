#pragma once
#include "Character.h"

Character::Character()
{

}

Character::Character(const Point point, const int HP, const int speed, const int attack, const int defense)
	: Object(point), m_HP(HP), m_speed(speed), m_attack(attack), m_defense(defense)
{
}

Character::~Character()
{
}

int Character::getHP()
{
	return m_HP;
}

int Character::getspeed()
{
	return m_speed;
}

int Character::getattack()
{
	return m_attack;
}

int Character::getdefense()
{
	return m_defense;
}

void Character::draw()
{
}

void Character::move()
{
}

void Character::attack()
{
}

void Character::update()
{
}
