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

	int m_state;

public:
	Monster();
	Monster(const Point point, const int HP, const int speed, const int attack, const int defense);
	~Monster();

	vector<int> GetPath();

	void SetState(int state);

	virtual void InsertBuffer(vector<string>& buffer) override;
	virtual void Update(float elapsedTime) override;

	virtual void Move(const int dir);
	void Attack() override; 
	virtual bool CollisionCheck(Point point) override;

	virtual bool IsValidPoint(Point point);
	virtual void AStar(Point goal);
	virtual bool IsFindPoint(shared_ptr<Node> current, Point goal);

	bool isObstacle(int x, int y);
	bool LineOfSight(const Point& start, const Point& end);
	bool isDetected(Point goal);
	bool isAttacked(Point goal);
};

