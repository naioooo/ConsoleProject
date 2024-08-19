#include "BossMonster.h"
#include "BossBehaviorTree.h"
#include "GameScene.h"

BossMonster::BossMonster()
{
}

BossMonster::BossMonster(const Point point, const int HP, const int speed, const int attack, const int defense)
	: Monster(point, HP, speed, attack, defense)
{
	m_behaviorTree = std::make_shared<SelectorNode>();

	auto attackSequence = make_shared<SequenceNode>();
	attackSequence->AddChild(make_shared<Boss_IsPlayerInAttackRangeCondition>());
	attackSequence->AddChild(make_shared<Boss_AttackActionNode>());

	auto chaseSequence = make_shared<SequenceNode>();
	chaseSequence->AddChild(make_shared<Boss_IsPlayerDetectedCondition>());
	chaseSequence->AddChild(make_shared<Boss_ChaseActionNode>());

	auto wanderSequence = std::make_shared<SequenceNode>();
	wanderSequence->AddChild(std::make_shared<Boss_IsPlayerNotDetectedCondition>());
	wanderSequence->AddChild(std::make_shared<Boss_WanderActionNode>());

	m_behaviorTree->AddChild(attackSequence);
	m_behaviorTree->AddChild(chaseSequence);
	m_behaviorTree->AddChild(wanderSequence);

	m_detectionRange = 15.0f;
	m_attackRange = 5.0f;
	m_chasePoint = Point(0, 0);
	m_speedCnt = 0.0f;
	m_state = WANDER;
}

BossMonster::~BossMonster()
{
}

void BossMonster::InsertBuffer(vector<string>& buffer)
{
	for (auto& fireball : m_fireball)
	{
		if (fireball->GetAlive())
		{
			fireball->InsertBuffer(buffer);
		}
	}

	int x = m_point.x;
	int y = m_point.y;

	buffer[y - 1][x - 1] = CH_BOSS1;
	buffer[y - 1][x] = CH_BOSS2;
	buffer[y - 1][x + 1] = CH_BOSS3;
	buffer[y][x - 1] = CH_BOSS1;
	buffer[y][x] = CH_BOSS2;
	buffer[y][x + 1] = CH_BOSS3;
	buffer[y + 1][x - 1] = CH_BOSS1;
	buffer[y + 1][x] = CH_BOSS2;
	buffer[y + 1][x + 1] = CH_BOSS3;

}

void BossMonster::Update(float elapsedTime)
{
	m_speedCnt += elapsedTime;

	if (m_speedCnt > m_speed)
	{
		auto self = static_pointer_cast<Monster>(shared_from_this());
		m_behaviorTree->Tick(self);
		m_speedCnt = 0.0f;
	}

	for (auto& fireball : m_fireball)
	{
		fireball->Update(elapsedTime);
	}

	auto newEnd = std::remove_if(m_fireball.begin(), m_fireball.end(), [](shared_ptr<FireBall>& fireball)
		{
			return !fireball->GetAlive();
		});

	m_fireball.erase(newEnd, m_fireball.end());
}

bool BossMonster::IsValidPoint(Point point)
{
	if (point.x < 1 || point.x >= MAX_WIDTH - 1 || point.y < 1 || point.y >= MAX_HEIGHT - 1)
	{
		return false;
	}

	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

	for (auto& object : gameobjects[OBSTACLE])
	{
		Point pos = object->GetPoint();


		if (pos.x >= m_point.x - 1 && pos.x <= m_point.x + 1 && pos.y >= m_point.y - 1 && pos.y <= m_point.y + 1)
		{
			return false;
		}
	}

	return true;
}

void BossMonster::ExplosiveFireBall(int width, int height)
{
	Point pos{ m_point.x - (width / 2), m_point.y - (height / 2) };

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			shared_ptr<FireBall> fireball = make_shared<FireBall>(Point(pos.x + x, pos.y + y), 1, m_dir, 3, 1);
			m_fireball.push_back(fireball);
		}
	}
}

void BossMonster::MeteorFireBall()
{
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<int> width(0, MAX_WIDTH - 1);
	uniform_int_distribution<int> height(0, MAX_HEIGHT - 1);

	int cnt = 0;

	while (true)
	{
		if (cnt > 5)
			break;

		Point pos = Point(width(gen), height(gen));

		if (CollisionCheck(pos))
		{
			shared_ptr<FireBall> fireball = make_shared<FireBall>(pos, 1, m_dir, 3, 1);
			m_fireball.push_back(fireball);
			cnt++;
		}
	}
}
