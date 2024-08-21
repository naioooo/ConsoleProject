#include "AttackUP.h"

AttackUP::AttackUP()
{
}

AttackUP::AttackUP(const Point point, const int lifetime, const int attackUP)
	: Item(point, lifetime), m_AttackUP(attackUP)
{
	m_name = "A";
}

AttackUP::~AttackUP()
{
}

int AttackUP::GetAttackUP()
{
	return m_AttackUP;
}

void AttackUP::InsertBuffer(vector<string>& buffer)
{
	buffer[m_point.y][m_point.x] = CH_ATTACKUP;
}

void AttackUP::Update(float elapsedTime)
{
	Item::Update(elapsedTime);
}
