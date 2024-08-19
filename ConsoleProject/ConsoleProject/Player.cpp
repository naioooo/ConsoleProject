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
	m_skillCnt = {5, 5, 5};
	m_killCnt = 0;
}

Player::~Player()
{
}

void Player::InsertBuffer(vector<string>& buffer)
{
	for (auto& bullet : m_bullets)
	{
		if (bullet->GetAlive())
		{
			bullet->InsertBuffer(buffer);
		}
	}

	buffer[m_point.y][m_point.x] = CH_PLAYER;
}

void Player::Update(float elapsedTime)
{
	for (auto& bullet : m_bullets)
	{
		bullet->Update(elapsedTime);
	}

	auto newEnd = std::remove_if(m_bullets.begin(), m_bullets.end(), [](shared_ptr<Bullet>& bullet)
		{
			return !bullet->GetAlive();
		});

	m_bullets.erase(newEnd, m_bullets.end());
}

unsigned int Player::GetMoney()
{
	return m_money;
}

int Player::GetKillCnt()
{
	return m_killCnt;
}

vector<int> Player::GetSkillCnt()
{
	return m_skillCnt;
}

void Player::SetMoney(const unsigned int money)
{
	m_money = money;
}

void Player::SetKillCnt(const int kill_cnt)
{
	m_killCnt = kill_cnt;
}

void Player::Input()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { //왼쪽
		m_dir = LEFT;
		Move();
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { //오른쪽	
		m_dir = RIGHT;
		Move();
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000) { //위
		m_dir = UP;
		Move();
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //아래
		m_dir = DOWN;
		Move();
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

			shared_ptr<Bullet> bullet = make_shared<Bullet>(m_point, 5, m_dir, 1, 10);
			m_bullets.push_back(bullet);
		}
	}
	else if (GetAsyncKeyState('A') & 0x8000)
	{
		if (m_skillCnt[0] > 0 && m_HP < 30)
		{
			m_HP++;
			if (m_HP > 30)
			{
				m_HP = 30;
			}

			m_skillCnt[0]--;
		}
	}
	else if (GetAsyncKeyState('S') & 0x8000)
	{
		if (m_skillCnt[1] > 0)
		{
			for (int dir = LEFT; dir <= RIGHTDOWN; dir++)
			{
				shared_ptr<Bullet> bullet = make_shared<Bullet>(m_point, 5, dir, 10, 3);
				m_bullets.push_back(bullet);
			}
			m_skillCnt[1]--;
		}
	}
	else if (GetAsyncKeyState('D') & 0x8000 && m_dir != 0)
	{
		if (m_skillCnt[2] > 0)
		{
			Point bulletPos = m_point;

			while (true)
			{
				switch (m_dir)
				{
				case LEFT:
					bulletPos.x -= 1;
					break;
				case RIGHT:
					bulletPos.x += 1;
					break;
				case UP:
					bulletPos.y -= 1;
					break;
				case DOWN:
					bulletPos.y += 1;
					break;
				}

				if (!CollisionCheck(bulletPos))
				{
					break;
				}

				shared_ptr<Bullet> bullet = make_shared<Bullet>(bulletPos, 5, m_dir, 10, 1);
				m_bullets.push_back(bullet);
			}

			m_skillCnt[2]--;
		}		
	}

	if (GetAsyncKeyState('Q') & 0x8000)
	{
		if (m_money >= 1000)
		{
			m_money -= 1000;
			m_skillCnt[0]++;

			if (m_skillCnt[0] > 9)
				m_skillCnt[0] = 9;
		}
	}
	else if (GetAsyncKeyState('W') & 0x8000)
	{
		if (m_money >= 1000)
		{
			m_money -= 1000;
			m_skillCnt[1]++;

			if (m_skillCnt[1] > 9)
				m_skillCnt[1] = 9;
		}
	}
	else if (GetAsyncKeyState('E') & 0x8000)
	{
		if (m_money >= 1000)
		{
			m_money -= 1000;
			m_skillCnt[2]++;

			if (m_skillCnt[2] > 9)
				m_skillCnt[2] = 9;
		}
	}
}

void Player::Move()
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

	if (CollisionCheck(next))
	{
		m_point = next;
	}
}

void Player::Attack()
{
}

bool Player::CollisionCheck(Point point)
{
	if (point.x < 0 || point.x >= MAX_WIDTH || point.y < 0 || point.y >= MAX_HEIGHT)
	{
		return false;
	}

	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

	for (auto& object : gameobjects[OBSTACLE])
	{
		if (object->GetPoint() == point)
		{
			return false;
		}
	}
	for (auto& object : gameobjects[MONSTER])
	{
		if (gameobjects[MONSTER].size() == 1)
		{

			shared_ptr<BossMonster> bossmonster = dynamic_pointer_cast<BossMonster>(object);
			if (bossmonster != nullptr)
			{
				Point pos = bossmonster->GetPoint(); 

				if (point.x >= pos.x - 1 && point.x <= pos.x + 1 && point.y >= pos.y - 1 && point.y <= pos.y + 1)
				{
					return false;
				}
			}
		}

		if (object->GetPoint() == point)
		{
			return false;
		}
	}
	for (auto& object : gameobjects[ITEM])
	{
		if (object->GetPoint() == point)
		{
			shared_ptr<Item> item = dynamic_pointer_cast<Item>(object);
			string name = item->GetName();

			if (name == "A")
			{
				shared_ptr<AttackUP> attackUP = dynamic_pointer_cast<AttackUP>(item);
				m_attack += attackUP->GetAttackUP(); 
				if (m_attack > 9999)
				{
					m_attack = 9999;
				}
			}
			else if (name == "H")
			{
				shared_ptr<HpUP> hpUP = dynamic_pointer_cast<HpUP>(item);
				m_HP += hpUP->GetHpUP();
				if (m_HP > 30)
				{
					m_HP = 30;
				}
			}
			else if (name == "M")
			{
				shared_ptr<Money> money = dynamic_pointer_cast<Money>(item);
				m_money += money->GetMoney();
				if (m_money > 99999)
				{
					m_money = 99999;
				}
			}

			item->SetAlive(false);
		}
	}

	return true;
}

