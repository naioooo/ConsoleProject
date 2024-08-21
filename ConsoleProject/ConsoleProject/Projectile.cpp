#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::Projectile(const Point point, const int speed, const int dir, const int damage, const int lifetime)
	: Object(point), m_speed(speed), m_dir(dir), m_damage(damage), m_lifetime(lifetime)
{
	m_speedCnt = 0;
	m_lifetimeCnt = 0;
}

Projectile::~Projectile()
{
}

void Projectile::Update(float elapsedTime)
{
	if (m_lifetimeCnt >= m_lifetime)
	{
		m_alive = false;
		return;
	}

	m_speedCnt += elapsedTime;
	if (m_speedCnt > m_speed)
	{
		Move(elapsedTime);
		m_speedCnt = 0.0f;
	}

	m_lifetimeCnt++;
}

void Projectile::Move(float elapsedTime)
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
