#include "fireBall.h"
#include "GameScene.h"

FireBall::FireBall()
{
}

FireBall::FireBall(const Point point, const int speed, const int dir, const int damage, const int lifetime)
	: Object(point), m_speedCnt(speed), m_dir(dir), m_damage(damage), m_lifetime(lifetime)
{
	m_speedCnt = 0;
	m_lifetimeCnt = 0;
}

FireBall::~FireBall()
{
}

void FireBall::InsertBuffer(vector<string>& buffer)
{
	buffer[m_point.y][m_point.x] = CH_fireBall;
}

void FireBall::Update(float elapsedTime)
{
	if (m_lifetimeCnt >= m_lifetime)
	{
		m_alive = false;
		return;
	}

	m_speedCnt += elapsedTime;
	if (m_speedCnt > 60.0f)
	{
		Move(elapsedTime);
		m_speedCnt = 0.0f;
	}

	m_lifetimeCnt++;
}

void FireBall::Move(float elapsedTime)
{
	Point next = m_point;

	switch (m_dir)
	{
	case RIGHT:
		if (next.x < MAX_WIDTH)
		{
			next.x++;
		}
		break;
	case LEFT:
		if (next.x >= 0)
		{
			next.x--;
		}
		break;
	case UP:
		if (next.y >= 0)
		{
			next.y--;
		}
		break;
	case DOWN:
		if (next.y < MAX_HEIGHT)
		{
			next.y++;
		}
		break;

	case LEFTUP:
		if (next.x >= 0 && next.y >= 0)
		{
			next.x--;
			next.y--;
		}
		break;
	case RIGHTUP:
		if (next.x < MAX_WIDTH && next.y >= 0)
		{
			next.x++;
			next.y--;
		}
		break;
	case LEFTDOWN:
		if (next.x >= 0 && next.y < MAX_HEIGHT)
		{
			next.x--;
			next.y++;
		}
		break;
	case RIGHTDOWN:
		if (next.x < MAX_WIDTH && next.y < MAX_HEIGHT)
		{
			next.x++;
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
	else
	{
		m_alive = false;
	}
}

bool FireBall::CollisionCheck(Point point)
{
	if (point.x < 0 || point.x >= MAX_WIDTH || point.y < 0 || point.y >= MAX_HEIGHT)
	{
		return false;
	}

	vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };

	for (auto& object : gameObjects[OBSTACLE])
	{
		if (object->GetPoint() == point)
		{
			return false;
		}
	}

	shared_ptr<Player> player = dynamic_pointer_cast<Player>(gameObjects[PLAYER][0]);
	
	if (player->GetPoint() == point)
	{
		int HP = player->GetHP() - m_damage;
		player->SetHP(HP);

		return false;
	}
	
	return true;
}
