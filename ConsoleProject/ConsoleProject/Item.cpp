#include "Item.h"

Item::Item()
{
}

Item::Item(const Point point, const int lifetime) : Object(point), m_lifetime(lifetime)
{
	m_lifetimeCnt = 0;
}

Item::~Item()
{
}

string Item::GetName() const
{
	return m_name;
}

void Item::Update(float elapsedTime)
{
	if (m_lifetimeCnt >= m_lifetime)
	{
		m_alive = false;
		return;
	}

	m_lifetimeCnt++;
}
