#pragma once
#include "Player.h"
#include "GameScene.h"

Player::Player()
{
}

Player::Player(const Point point, const int HP, const int speed, const int attack, const int defense, const string& name)
	: Character(point, HP, speed, attack, defense), m_name(name)
{
}

Player::~Player()
{
}

void Player::insertbuffer(vector<string>& buffer)
{
	buffer[m_point.y][m_point.x] = '@';
}

void Player::update()
{
}

void Player::move()
{
	Point next = m_point;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { //왼쪽
		if (next.x > 0)
		{
			next.x -= m_speed;
		}		
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { //오른쪽		
		if (next.x < MAX_WIDTH - 1 - m_speed)
		{
			next.x += m_speed;
		}
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) { //위
		if (next.y > 0)
		{
			next.y -= m_speed;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //아래
		if (next.y < MAX_HEIGHT - 1 - m_speed)
		{
			next.y += m_speed;
		}
	}

	if (collision_check(next))
	{
		m_point = next;
	}
}

void Player::attack()
{
}

bool Player::collision_check(Point point)
{
	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

	for (int i = 0; i < 5; i++)
	{
		if (i != PLAYER)
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

