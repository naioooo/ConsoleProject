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

	Point GetPoint() const;
	bool GetAlive() const;

	void SetAlive(bool alive);
	void SetPoint(Point point);

	virtual void InsertBuffer(vector<string>& buffer);
	virtual void Update(float elapsedTime);
	virtual bool CollisionCheck(Point point);
};

