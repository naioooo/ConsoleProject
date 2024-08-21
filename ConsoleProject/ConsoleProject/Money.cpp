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

int Money::GetMoney() const
{
	return m_money;
}

void Money::InsertBuffer(vector<string>& buffer)
{
	buffer[m_point.y][m_point.x] = CH_MONEY;
}

void Money::Update(float elapsedTime)
{
	Item::Update(elapsedTime);
}
