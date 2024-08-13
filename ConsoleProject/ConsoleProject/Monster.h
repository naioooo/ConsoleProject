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
	float gCost, hCost; // gCost: ���������� �� �������� ���� �Ÿ�, hCost: �� ��忡�� ��ǥ������ ���� �Ÿ�
	Node* parent;

	// fCost ���
	float fCost() const { return gCost + hCost; }

	// ������ ���� �� ������
	bool operator>(const Node& other) const 
	{
		return fCost() > other.fCost();
	}
};
