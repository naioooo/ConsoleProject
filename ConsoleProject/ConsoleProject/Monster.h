#pragma once
#include "Character.h"

class SelectorNode;

//class Monster : public enable_shared_from_this<Monster> , Character
class Monster : public Character
{
private:
	shared_ptr<SelectorNode> m_behaviortree; 
	vector<int> m_path;

public:
	Monster();
	Monster(const Point point, const int HP, const int speed, const int attack, const int defense);
	~Monster();

	vector<int> getpath();

	void insertbuffer(vector<string>& buffer) override;
	void update() override;

	void move(const int dir);
	void attack() override; 
	bool collision_check(Point point) override;

	bool IsValidPoint(Point point);
	void AStar(Point goal);
};

struct Node
{
	Point position;
	float gCost, hCost; // gCost: 시작점에서 이 노드까지의 실제 거리, hCost: 이 노드에서 목표까지의 추정 거리
	Node* parent;

	// fCost 계산
	float fCost() const { return gCost + hCost; }

	// 정렬을 위한 비교 연산자
	bool operator>(const Node& other) const 
	{
		return fCost() > other.fCost();
	}
};
