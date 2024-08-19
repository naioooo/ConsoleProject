#pragma once
#include "Object.h"
class Item : public Object
{
protected:
	string m_name;

	int m_lifetime;
	int m_lifetimeCnt;

public:
	Item();
	Item(const Point point, const int lifetime);
	~Item();

	string GetName();

	virtual void Update(float elapsedTime) override;
};

