#pragma once
#include "Player.h"
#include "GameScene.h"

Player::Player()
{
}

Player::Player(const Point point, const int HP, const int speed, const int attack, const int defense, const string& name)
	: Character(point, HP, speed, attack, defense), m_name(name)
{
	m_money = 1000;
}

Player::~Player()
{
}

void Player::insertbuffer(vector<string>& buffer)
{
	for (auto& bullet : m_bullets)
	{
		if (bullet->getalive())
		{
			bullet->insertbuffer(buffer);
		}
	}

	buffer[m_point.y][m_point.x] = '@';
}

void Player::update(float elapsedTime)
{
	for (auto& bullet : m_bullets)
	{
		bullet->update(elapsedTime);
	}

	auto newEnd = std::remove_if(m_bullets.begin(), m_bullets.end(), [](shared_ptr<Bullet>& bullet)
		{
			return !bullet->getalive();
		});

	m_bullets.erase(newEnd, m_bullets.end());
}

unsigned int Player::getmoney()
{
	return m_money;
}

void Player::setmoney(const unsigned int money)
{
	m_money = money;
}

void Player::input()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { //왼쪽
		m_dir = LEFT;
		move();
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { //오른쪽	
		m_dir = RIGHT;
		move();
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000) { //위
		m_dir = UP;
		move();
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //아래
		m_dir = DOWN;
		move();
	}

	if (GetAsyncKeyState(VK_CONTROL) & 0x8001)
	{
		if (m_dir != 0)
		{
			Point bullet_pos = m_point;

			switch (m_dir)
			{
			case LEFT:
				bullet_pos.x -= 1;
				break;
			case RIGHT:
				bullet_pos.x += 1;
				break;
			case UP:
				bullet_pos.y -= 1;
				break;
			case DOWN:
				bullet_pos.y += 1;
				break;
			}

			shared_ptr<Bullet> bullet = make_shared<Bullet>(m_point, 5, m_dir, 10, 10);
			m_bullets.push_back(bullet);
		}
	}
}

void Player::move()
{
	Point next = m_point;

	switch (m_dir)
	{
	case LEFT:
		if (next.x > 0)
		{
			next.x -= m_speed;
		}
		break;
	case RIGHT:
		if (next.x < MAX_WIDTH - 1)
		{
			next.x += m_speed;
		}
		break;
	case UP:
		if (next.y > 0)
		{
			next.y -= m_speed;
		}
		break;
	case DOWN:
		if (next.y < MAX_HEIGHT - 1)
		{
			next.y += m_speed;
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

void Player::attack()
{
}

bool Player::collision_check(Point point)
{
	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

	for (int i = 0; i < 4; i++)
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

