#include "Monster.h"

Monster::Monster()
{
}

Monster::Monster(const Point point, const int HP, const int speed, const int attack, const int defense)
	: Character(point, HP, speed, attack, defense)
{
}

Monster::~Monster()
{
}

void Monster::move(const DIR dir)
{
	switch (dir)
	{
	case RIGHT:
		if (m_point.x < MAX_WIDTH - 2)
		{
			m_point.x++;
		}
		break;
	case LEFT:
		if (m_point.x > 0)
		{
			m_point.x--;
		}
		break;
	case UP:
		if (m_point.y > 0)
		{
			m_point.y--;
		}
		break;
	case DOWN:
		if (m_point.y < MAX_HEIGHT - 2)
		{
			m_point.y++;
		}
		break;

	default:
		break;
	}
}

void Monster::attack()
{
}

void Monster::update()
{
	move(RIGHT);
}

void Monster::insertbuffer(vector<string>& buffer)
{
	buffer[m_point.y][m_point.x] = '#';
}
