#include "Bullet.h"
#include "GameScene.h"

Bullet::Bullet()
{
}

Bullet::Bullet(const Point point, const int speed, const int dir, const int damage): Object(point), m_speed(speed), m_dir(dir), m_damage(damage)
{
}

Bullet::~Bullet()
{
}

void Bullet::insertbuffer(vector<string>& buffer)
{
    buffer[m_point.y][m_point.x] = '*';
}

void Bullet::update(float elapsedTime)
{
	move(elapsedTime);
}

void Bullet::move(float elapsedTime)
{
	Point next = m_point;

	switch (m_dir)
	{
	case RIGHT:
		if (next.x < MAX_WIDTH)
		{
			next.x += m_speed * elapsedTime * 0.001f;
		}
		break;
	case LEFT:
		if (next.x >= 0)
		{
			next.x -= m_speed * elapsedTime * 0.001f;
		}
		break;
	case UP:
		if (next.y >= 0)
		{
			next.y -= m_speed * elapsedTime * 0.001f;
		}
		break;
	case DOWN:
		if (next.y < MAX_HEIGHT)
		{
			next.y += m_speed * elapsedTime * 0.001f;
		}
		break;

	default:
		break;
	}

	if (collision_check(next))
	{
		m_point = next;
	}
	else
	{
		m_alive = false;
	}
}

bool Bullet::collision_check(Point point)
{
	if (point.x < 0 || point.x >= MAX_WIDTH || point.y < 0 || point.y >= MAX_HEIGHT)
	{
		return false;
	}

	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

	for (auto& object : gameobjects[OBSTACLE])
	{
		if (object->getpoint() == point)
		{
			return false;
		}
	}

	for (auto& object : gameobjects[MONSTER])
	{
		if (object->getpoint() == point)
		{
			object->setalive(false);
			return false;
		}
	}

	return true;
}
