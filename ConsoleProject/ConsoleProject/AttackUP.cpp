#include "AttackUP.h"

AttackUP::AttackUP()
{
}

AttackUP::AttackUP(const Point point, const int lifetime, const int AttackUP)
	: Item(point, lifetime), m_AttackUP(AttackUP)
{
	m_name = "A";
}

AttackUP::~AttackUP()
{
}

int AttackUP::getAttackUP()
{
	return m_AttackUP;
}

void AttackUP::insertbuffer(vector<string>& buffer)
{
	buffer[m_point.y][m_point.x] = CH_ATTACKUP;
}

void AttackUP::update(float elapsedTime)
{
	Item::update(elapsedTime);
}
