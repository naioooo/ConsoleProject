#include "Item.h"

Item::Item()
{
}

Item::Item(const Point point, const int lifetime) : Object(point), m_lifetime(lifetime)
{
	m_lifetime_cnt = 0;
}

Item::~Item()
{
}

string Item::getname()
{
	return m_name;
}

void Item::update(float elapsedTime)
{
	if (m_lifetime_cnt >= m_lifetime)
	{
		m_alive = false;
		return;
	}

	m_lifetime_cnt++;
}
