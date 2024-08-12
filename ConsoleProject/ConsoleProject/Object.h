#pragma once
#include "Library.h"

class Object
{
protected:
	Point m_point;

public:
	Object();
	Object(const Point point);
	~Object();

	Point getpoint();

	virtual void draw();
	virtual void insertbuffer(vector<string>& buffer);

};

