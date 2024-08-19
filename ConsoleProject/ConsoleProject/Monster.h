#pragma once
#include "Character.h"

class SelectorNode;

class Monster : public Character
{
protected:
	shared_ptr<SelectorNode> m_behaviorTree; 
	vector<int> m_path;
	float m_detectionRange;
	float m_attackRange;

	Point m_chasePoint;

	int m_state;

public:
	Monster();
	Monster(const Point point, const int HP, const int speed, const int attack, const int defense);
	~Monster();

	vector<int> GetPath();
	Point GetChasePoint();

	void SetChasePoint(Point point);
	void SetState(int state);

	virtual void InsertBuffer(vector<string>& buffer) override;
	virtual void Update(float elapsedTime) override;

	void Move(const int dir);
	void Attack() override; 
	bool CollisionCheck(Point point) override;

	virtual bool IsValidPoint(Point point);
	void AStar(Point goal);

	bool isObstacle(int x, int y);
	bool LineOfSight(const Point& start, const Point& end);
	bool isDetected(Point goal);
	bool isAttacked(Point goal);
};

