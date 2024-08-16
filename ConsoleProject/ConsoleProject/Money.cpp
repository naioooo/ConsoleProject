#include "Money.h"

Money::Money()
{
}

Money::Money(const Point point, const int lifetime, const int money)
	: Item(point, lifetime), m_money(money)
{
	m_name = "M";
}

Money::~Money()
{
}

int Money::getmoney()
{
	return m_money;
}

void Money::insertbuffer(vector<string>& buffer)
{
	buffer[m_point.y][m_point.x] = CH_MONEY;
}

void Money::update(float elapsedTime)
{
	Item::update(elapsedTime);
}
