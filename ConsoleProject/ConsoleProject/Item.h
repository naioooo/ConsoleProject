#pragma once
#include "Object.h"
class Item : public Object
{
protected:
	string m_name;

	int m_lifetime;
	int m_lifetime_cnt;

public:
	Item();
	Item(const Point point, const int lifetime);
	~Item();

	string getname();

	virtual void update(float elapsedTime) override;
};

