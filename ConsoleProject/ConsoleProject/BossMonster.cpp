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

	// 공격중인지
	auto attackSequence = make_shared<SequenceNode>();
	attackSequence->AddChild(make_shared<Boss_IsAttackingNowCondition>());
	attackSequence->AddChild(make_shared<Boss_AttackActionNode>());

	// 쿨타임인지
	auto choiceAttackSequence = make_shared<SequenceNode>();
	choiceAttackSequence->AddChild(make_shared<Boss_IsTimeToAttackCondition>());

	// 돌아다니기
	auto wanderSequence = std::make_shared<SequenceNode>();
	wanderSequence->AddChild(std::make_shared<Boss_WanderActionNode>());

	m_behaviorTree->AddChild(attackSequence);
	m_behaviorTree->AddChild(choiceAttackSequence);
	m_behaviorTree->AddChild(wanderSequence);

	m_detectionRange = 15.0f;
	m_attackRange = 5.0f;

	m_state = WANDER;

	m_coolTime = 10;
	m_coolTimeCnt = 0;

	m_isAttack = 0;

	m_attackTime = 0;
	m_attackTimeCnt = 0;

	m_speedCnt = 0.0f;
}

BossMonster::~BossMonster()
{
}

void BossMonster::InsertBuffer(vector<string>& buffer)
{
	for (auto& fireBall : m_fireBall)
	{
		if (fireBall->GetAlive())
		{
			fireBall->InsertBuffer(buffer);
		}
	}

	buffer[m_point.y - 1][m_point.x - 1] = CH_BOSS1;
	buffer[m_point.y - 1][m_point.x] = CH_BOSS2;
	buffer[m_point.y - 1][m_point.x + 1] = CH_BOSS3;
	buffer[m_point.y][m_point.x - 1] = CH_BOSS1;
	if(m_state == ATTACK)
		buffer[m_point.y][m_point.x] = CH_MONSTER3;
	else if (m_state == WANDER)
		buffer[m_point.y][m_point.x] = CH_BOSS2;
	buffer[m_point.y][m_point.x + 1] = CH_BOSS3;
	buffer[m_point.y + 1][m_point.x - 1] = CH_BOSS1;
	buffer[m_point.y + 1][m_point.x] = CH_BOSS2;
	buffer[m_point.y + 1][m_point.x + 1] = CH_BOSS3;

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

	for (auto& fireBall : m_fireBall)
	{
		fireBall->Update(elapsedTime);
	}

	auto newEnd = std::remove_if(m_fireBall.begin(), m_fireBall.end(), [](shared_ptr<FireBall>& fireBall)
		{
			return !fireBall->GetAlive();
		});

	m_fireBall.erase(newEnd, m_fireBall.end());
}

void BossMonster::Move(const int dir)
{
	Point next = m_point;

	switch (dir)
	{
	case RIGHT:
		if (next.x < MAX_WIDTH - 1)
		{
			next.x++;
		}
		break;
	case LEFT:
		if (next.x > 1)
		{
			next.x--;
		}
		break;
	case UP:
		if (next.y > 1)
		{
			next.y--;
		}
		break;
	case DOWN:
		if (next.y < MAX_HEIGHT - 1)
		{
			next.y++;
		}
		break;

	default:
		break;
	}

	if (CollisionCheck(next))
	{
		m_point = next;
	}
}

bool BossMonster::CollisionCheck(Point point)
{
	if (point.x < 1 || point.x >= MAX_WIDTH - 1 || point.y < 1 || point.y >= MAX_HEIGHT - 1)
	{
		return false;
	}

	vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };
	Point m_point{};

	for (auto& object : gameObjects[OBSTACLE])
	{
		m_point = object->GetPoint();

		if (m_point.x > point.x - 2 && m_point.x < point.x + 2 &&
			m_point.y > point.y - 2 && m_point.y < point.y + 2)
		{
			return false;
		}
	}	

	m_point = gameObjects[PLAYER][0]->GetPoint();

	if (m_point.x > point.x - 2 && m_point.x < point.x + 2 &&
		m_point.y > point.y - 2 && m_point.y < point.y + 2)
	{
		shared_ptr<Player> player = dynamic_pointer_cast<Player>(gameObjects[PLAYER][0]);
		if (!player->GetInvincibility())
		{
			player->SetHP(player->GetHP() - 1);
		}
		return false;
	}

	return true;
}

bool BossMonster::IsValidPoint(Point point)
{
	if (point.x < 1 || point.x >= MAX_WIDTH - 1 || point.y < 1 || point.y >= MAX_HEIGHT - 1)
	{
		return false;
	}

	vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };
	Point p{};

	for (auto& object : gameObjects[OBSTACLE])
	{
		p = object->GetPoint();

		if (p.x > point.x - 2 && p.x < point.x + 2 &&
			p.y > point.y - 2 && p.y < point.y + 2)
		{
			return false;
		}
	}

	return true;
}

bool BossMonster::IsFindPoint(shared_ptr<Node> current, Point goal)
{
	if (goal.x > current->position.x - 2 && goal.x < current->position.x + 2 &&
		goal.y > current->position.y - 2 && goal.y < current->position.y + 2)
	{
		return true;
	}

	return false;
}

int BossMonster::GetCoolTime() const
{
	return m_coolTime;
}

int BossMonster::GetCoolTimeCnt() const
{
	return m_coolTimeCnt;
}

int BossMonster::GetIsAttack() const
{
	return m_isAttack;
}

int BossMonster::GetAttackTime() const
{
	return m_attackTime;
}

int BossMonster::GetAttackTimeCnt() const
{
	return m_attackTimeCnt;
}

void BossMonster::SetCoolTime(int coolTime)
{
	m_coolTime = coolTime;
}

void BossMonster::SetCoolTimeCnt(int coolTimeCnt)
{
	m_coolTimeCnt = coolTimeCnt;
}

void BossMonster::SetIsAttack(int isAttack)
{
	m_isAttack = isAttack;
}

void BossMonster::SetAttackTime(int attackTime)
{
	m_attackTime = attackTime;
}

void BossMonster::SetAttackTimeCnt(int attackTimeCnt)
{
	m_attackTimeCnt = attackTimeCnt;
}

void BossMonster::ChargeAttack()
{
	Move(m_dir);
}

void BossMonster::ChasePlayer()
{
	vector<vector<shared_ptr<Object>>> gameObjects = GameScene::m_gameObjects;

	AStar(gameObjects[PLAYER][0]->GetPoint());
	Move(GetPath()[0]);
}

void BossMonster::ExplosiveFireBall(int width, int height)
{
	m_fireBall.push_back(make_shared<FireBall>(Point(m_point.x - 2, m_point.y - 2), 60, LEFTUP, 1, 50));
	m_fireBall.push_back(make_shared<FireBall>(Point(m_point.x + 2, m_point.y - 2), 60, RIGHTUP, 1, 50));
	m_fireBall.push_back(make_shared<FireBall>(Point(m_point.x - 2, m_point.y + 2), 60, LEFTDOWN, 1, 50));
	m_fireBall.push_back(make_shared<FireBall>(Point(m_point.x + 2, m_point.y + 2), 60, RIGHTDOWN, 1, 50));

	for (int i = -1; i <= 1; i++)
	{
		m_fireBall.push_back(make_shared<FireBall>(Point(m_point.x + i, m_point.y - 2), 60, UP, 1, 50));
	}
	for (int i = -1; i <= 1; i++)
	{
		m_fireBall.push_back(make_shared<FireBall>(Point(m_point.x + i, m_point.y + 2), 60, DOWN, 1, 50));
	}
	for (int i = -1; i <= 1; i++)
	{
		m_fireBall.push_back(make_shared<FireBall>(Point(m_point.x - 2, m_point.y - i), 60, LEFT, 1, 50));
	}
	for (int i = -1; i <= 1; i++)
	{
		m_fireBall.push_back(make_shared<FireBall>(Point(m_point.x + 2, m_point.y + i), 60, RIGHT, 1, 50));
	}	

	m_isAttack = 7;
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
		if (cnt > 20)
			break;

		Point m_point = Point(width(gen), height(gen));

		if (CollisionCheck(m_point))
		{
			shared_ptr<FireBall> fireBall = make_shared<FireBall>(m_point, 1, 0, 3, 10);
			m_fireBall.push_back(fireBall);
			cnt++;
		}
	}

	m_isAttack = 7;
}

void BossMonster::DirectionalBlast()
{
	int newX = m_point.x;
	int newY = m_point.y;

	switch (m_dir)
	{
	case LEFT:
		newX -= 2;
		break;
	case RIGHT:
		newX += 2;
		break;
	case UP:
		newY -= 2;
		break;
	case DOWN:
		newY += 2;
		break;
	}

	switch (m_dir)
	{
	case LEFT:
	case RIGHT:
		for (int i = -3; i <= 3; i++)
		{			
			shared_ptr<FireBall> fireBall = make_shared<FireBall>(Point(newX, newY + i), 60, m_dir, 3, 100);
			m_fireBall.push_back(fireBall);
		}
		break;
	case UP:
	case DOWN:
		for (int i = -3; i <= 3; i++)
		{
			shared_ptr<FireBall> fireBall = make_shared<FireBall>(Point(newX + i, newY), 60, m_dir, 3, 100);
			m_fireBall.push_back(fireBall);
		}
		break;
	}

	m_isAttack = 7;
}

void BossMonster::FireBallFromMapEdges()
{
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<int> edges(1, 4);

	int edge = edges(gen); 
	Point newm_point{};

	switch (edge)
	{
	case LEFT:
		for (int i = 0; i < MAX_HEIGHT; i += 2)
		{
			shared_ptr<FireBall> fireBall = make_shared<FireBall>(Point(0, i), 30, RIGHT, 3, 300);
			m_fireBall.push_back(fireBall);
		}
		break;
	case RIGHT:
		for (int i = 1; i < MAX_HEIGHT; i += 2)
		{
			shared_ptr<FireBall> fireBall = make_shared<FireBall>(Point(MAX_WIDTH - 1, i), 30, LEFT, 3, 300);
			m_fireBall.push_back(fireBall);
		}
		break;
	case UP:
		for (int i = 0; i < MAX_WIDTH; i += 2)
		{
			shared_ptr<FireBall> fireBall = make_shared<FireBall>(Point(i, 0), 30, DOWN, 3, 300);
			m_fireBall.push_back(fireBall);
		}
		break;
	case DOWN:
		for (int i = 1; i < MAX_WIDTH; i += 2)
		{
			shared_ptr<FireBall> fireBall = make_shared<FireBall>(Point(i, MAX_HEIGHT - 1 ), 30, UP, 3, 300);
			m_fireBall.push_back(fireBall);
		}
		break;
	}
		
	m_isAttack = 7;
}
