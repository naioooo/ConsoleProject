#pragma once
#include "Library.h"

class Object : public enable_shared_from_this<Object>
{
protected:
	Point m_point;
	bool m_alive;

public:
	Object();
	Object(const Point point);
	~Object();

	Point getpoint();
	bool getalive();

	void setalive(bool alive);

	virtual void insertbuffer(vector<string>& buffer);
	virtual void update(float elapsedTime);
	virtual bool collision_check(Point point);
};

