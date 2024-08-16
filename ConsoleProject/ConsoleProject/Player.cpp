#pragma once
#include "Player.h"
#include "GameScene.h"
#include "Item.h"
#include "HPUP.h"
#include "AttackUP.h"
#include "Money.h"

Player::Player()
{
}

Player::Player(const Point point, const int HP, const int speed, const int attack, const int defense, const string& name)
	: Character(point, HP, speed, attack, defense), m_name(name)
{
	m_money = 1000;
	m_skill_cnt = {5, 5, 5};
	m_kill_cnt = 0;
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

	buffer[m_point.y][m_point.x] = CH_PLAYER;
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

int Player::getkill_cnt()
{
	return m_kill_cnt;
}

vector<int> Player::getskill_cnt()
{
	return m_skill_cnt;
}

void Player::setmoney(const unsigned int money)
{
	m_money = money;
}

void Player::setkill_cnt(const int kill_cnt)
{
	m_kill_cnt = kill_cnt;
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

	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
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
	else if (GetAsyncKeyState('A') & 0x8000)
	{
		if (m_skill_cnt[0] > 0 && m_HP < 30)
		{
			m_HP++;
			if (m_HP > 30)
			{
				m_HP = 30;
			}

			m_skill_cnt[0]--;
		}
	}
	else if (GetAsyncKeyState('S') & 0x8000)
	{
		if (m_skill_cnt[1] > 0)
		{
			for (int dir = LEFT; dir <= RIGHTDOWN; dir++)
			{
				shared_ptr<Bullet> bullet = make_shared<Bullet>(m_point, 5, dir, 10, 3);
				m_bullets.push_back(bullet);
			}
			m_skill_cnt[1]--;
		}
	}
	else if (GetAsyncKeyState('D') & 0x8000 && m_dir != 0)
	{
		if (m_skill_cnt[2] > 0)
		{
			Point bullet_pos = m_point;

			while (true)
			{
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

				if (!collision_check(bullet_pos))
				{
					break;
				}

				shared_ptr<Bullet> bullet = make_shared<Bullet>(bullet_pos, 5, m_dir, 10, 1);
				m_bullets.push_back(bullet);
			}

			m_skill_cnt[2]--;
		}		
	}

	if (GetAsyncKeyState('Q') & 0x8000)
	{
		if (m_money >= 1000)
		{
			m_money -= 1000;
			m_skill_cnt[0]++;

			if (m_skill_cnt[0] > 9)
				m_skill_cnt[0] = 9;
		}
	}
	else if (GetAsyncKeyState('W') & 0x8000)
	{
		if (m_money >= 1000)
		{
			m_money -= 1000;
			m_skill_cnt[1]++;

			if (m_skill_cnt[1] > 9)
				m_skill_cnt[1] = 9;
		}
	}
	else if (GetAsyncKeyState('E') & 0x8000)
	{
		if (m_money >= 1000)
		{
			m_money -= 1000;
			m_skill_cnt[2]++;

			if (m_skill_cnt[2] > 9)
				m_skill_cnt[2] = 9;
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
			return false;
		}
	}
	for (auto& object : gameobjects[ITEM])
	{
		if (object->getpoint() == point)
		{
			shared_ptr<Item> item = dynamic_pointer_cast<Item>(object);
			string name = item->getname();

			if (name == "A")
			{
				shared_ptr<AttackUP> attackUP = dynamic_pointer_cast<AttackUP>(item);
				m_attack += attackUP->getAttackUP(); 
				if (m_attack > 9999)
				{
					m_attack = 9999;
				}
			}
			else if (name == "H")
			{
				shared_ptr<HpUP> hpUP = dynamic_pointer_cast<HpUP>(item);
				m_HP += hpUP->getHpUP();
				if (m_HP > 30)
				{
					m_HP = 30;
				}
			}
			else if (name == "M")
			{
				shared_ptr<Money> money = dynamic_pointer_cast<Money>(item);
				m_money += money->getmoney();
				if (m_money > 99999)
				{
					m_money = 99999;
				}
			}

			item->setalive(false);
		}
	}

	return true;
}

