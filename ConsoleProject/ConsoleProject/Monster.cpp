#include "Monster.h"
#include "MonsterBehaviorTree.h"
#include "GameScene.h"

Monster::Monster()
{
	
}

Monster::Monster(const Point point, const int HP, const int speed, const int attack, const int defense)
	: Character(point, HP, speed, attack, defense)
{
	m_behaviortree = std::make_shared<SelectorNode>();

	auto attackSequence = make_shared<SequenceNode>();
	attackSequence->AddChild(make_shared<IsPlayerInAttackRangeCondition>());
	attackSequence->AddChild(make_shared<AttackActionNode>());

	auto chaseSequence = make_shared<SequenceNode>();
	chaseSequence->AddChild(make_shared<IsPlayerDetectedCondition>());
	chaseSequence->AddChild(make_shared<ChaseActionNode>());

	auto wanderSequence = std::make_shared<SequenceNode>();
	wanderSequence->AddChild(std::make_shared<IsPlayerNotDetectedCondition>());
	wanderSequence->AddChild(std::make_shared<WanderActionNode>());

	m_behaviortree->AddChild(attackSequence);
	m_behaviortree->AddChild(chaseSequence);
	m_behaviortree->AddChild(wanderSequence);
}

Monster::~Monster()
{
}

vector<int> Monster::getpath()
{
	return m_path;
}

void Monster::insertbuffer(vector<string>& buffer)
{
	buffer[m_point.y][m_point.x] = '!';
}

void Monster::update()
{
	auto self = static_pointer_cast<Monster>(shared_from_this());
	m_behaviortree->Tick(self);
}

void Monster::move(const int dir)
{
	Point next = m_point;

	switch (dir)
	{
	case RIGHT:
		if (next.x < MAX_WIDTH - 2)
		{
			next.x++;
		}
		break;
	case LEFT:
		if (next.x > 0)
		{
			next.x--;
		}
		break;
	case UP:
		if (next.y > 0)
		{
			next.y--;
		}
		break;
	case DOWN:
		if (next.y < MAX_HEIGHT - 2)
		{
			next.y++;
		}
		break;

	default:
		break;
	}

	if (collision_check(next))
	{
		m_point = next;
	}
}

void Monster::attack()
{
}

bool Monster::collision_check(Point point)
{
	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };
	
	for (int i = 0; i < 5; i++)
	{
		if (i != MONSTER)
		{
			for (auto& object : gameobjects[i])
			{
				if (object->getpoint() == point)
				{
					return false;
				}
			}
		}
	}

	return true;
}

// 휴리스틱 함수: 맨해튼 거리
float Heuristic(Point a, Point b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

bool Monster::IsValidPoint(Point point)
{
	if (point.x < 0 || point.x >= MAX_WIDTH || point.y < 0 || point.y >= MAX_HEIGHT)
	{
		return false;
	}

	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

	for (int i = 0; i < 5; i++)
	{
		if (i != MONSTER && i != PLAYER)
		{
			for (auto& object : gameobjects[i])
			{
				if (object->getpoint() == point)
				{
					return false;
				}
			}
		}
	}

	return true;
}

void Monster::AStar(Point goal)
{
	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

	Point start = m_point;
	priority_queue<Node*, vector<Node*>, greater<Node*>> openSet;
	unordered_map<Point, Node*> allNodes;

	Node* startNode = new Node{ start , 0, Heuristic(start, goal), nullptr };
	openSet.push(startNode); 
	allNodes[start] = startNode;

	while (true)
	{
		if (openSet.empty())
		{
			break;
		}

		Node* current = openSet.top();
		openSet.pop();

		if (current->position == goal) {
			vector<int> pathDirections;
			Node* node = current;
			while (node->parent) {
				if (node->position.x == node->parent->position.x - 1) 
					pathDirections.push_back(LEFT);
				if (node->position.x == node->parent->position.x + 1)
					pathDirections.push_back(RIGHT);
				if (node->position.y == node->parent->position.y - 1)
					pathDirections.push_back(UP);
				if (node->position.y == node->parent->position.y + 1) 
					pathDirections.push_back(DOWN);
				node = node->parent;
			}

			reverse(pathDirections.begin(), pathDirections.end());
			m_path = pathDirections;			
			return;
		}

		vector<pair<Point, int>> directions =
		{
				{Point(-1, 0), LEFT},
				{Point(1, 0), RIGHT },
				{Point(0, -1), UP},
				{Point(0, 1), DOWN}
		};

		for (const auto& direction : directions)
		{
			Point newPos = { current->position.x + direction.first.x, current->position.y + direction.first.y };

			if (IsValidPoint(newPos))
			{
				float newGCost = current->gCost + 1.0f;
				float newHCost = Heuristic(newPos, goal);
				Node* neighbor = nullptr;

				if (allNodes.count(newPos)) 
				{
					neighbor = allNodes[newPos];
					if (newGCost >= neighbor->gCost)
						continue; // 기존 경로가 더 좋음
				}
				else 
				{
					neighbor = new Node{ newPos, (std::numeric_limits<float>::max)(), newHCost, current };
					allNodes[newPos] = neighbor;
				}

				neighbor->gCost = newGCost;
				openSet.push(neighbor);
			}
		}
	}

	return; 
}
