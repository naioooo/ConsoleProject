#include "HPUP.h"

HpUP::HpUP()
{
}

HpUP::HpUP(const Point point, const int lifetime, const int HpUP)
	: Item(point, lifetime), m_HpUP(HpUP)
{
	m_name = "H";
}

HpUP::~HpUP()
{
}

int HpUP::getHpUP()
{
	return m_HpUP;
}

void HpUP::insertbuffer(vector<string>& buffer)
{
	buffer[m_point.y][m_point.x] = CH_HPUP;
}

void HpUP::update(float elapsedTime)
{
	Item::update(elapsedTime);
}
