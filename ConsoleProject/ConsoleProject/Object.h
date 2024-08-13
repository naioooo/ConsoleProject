#pragma once
#include "Library.h"

class Object : public enable_shared_from_this<Object>
{
protected:
	Point m_point;

public:
	Object();
	Object(const Point point);
	~Object();

	Point getpoint();

	virtual void insertbuffer(vector<string>& buffer);
	virtual void update();
	virtual bool collision_check(Point point);
};

