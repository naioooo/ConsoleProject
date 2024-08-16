#include "Bullet.h"
#include "GameScene.h"
#include "Item.h"
#include "HPUP.h"
#include "AttackUP.h"
#include "Money.h"

Bullet::Bullet()
{
}

Bullet::Bullet(const Point point, const int speed, const int dir, const int damage, const int lifetime)
	: Object(point), m_speed_cnt(speed), m_dir(dir), m_damage(damage), m_lifetime(lifetime)
{
	m_speed_cnt = 0;
	m_lifetime_cnt = 0;
}

Bullet::~Bullet()
{
}

void Bullet::insertbuffer(vector<string>& buffer)
{
    buffer[m_point.y][m_point.x] = CH_BULLET;
}

void Bullet::update(float elapsedTime)
{
	if (m_lifetime_cnt >= m_lifetime)
	{
		m_alive = false;
		return;
	}

	m_speed_cnt += elapsedTime;
	if (m_speed_cnt > 120.0f)
	{
		move(elapsedTime);
		m_speed_cnt = 0.0f;
	}

	m_lifetime_cnt++;
}

void Bullet::move(float elapsedTime)
{
	Point next = m_point;

	switch (m_dir)
	{
	case RIGHT:
		if (next.x < MAX_WIDTH)
		{
			next.x ++;
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
			next.y --;
		}
		break;
	case DOWN:
		if (next.y < MAX_HEIGHT)
		{
			next.y ++;
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
			shared_ptr<Monster> monster = dynamic_pointer_cast<Monster>(object);
			int HP = monster->getHP() - m_damage;
			if (HP <= 0)
			{
				vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

				shared_ptr<Player> player = dynamic_pointer_cast<Player>(gameobjects[PLAYER][0]);
				player->setkill_cnt(player->getkill_cnt() + 1);

				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<int> rand(0, 4);

				shared_ptr<Item> item;

				switch (rand(gen))
				{
				case 0:
					item = make_shared<AttackUP>(monster->getpoint(), 20, 5);
					break;
				case 1:
					item = make_shared<HpUP>(monster->getpoint(), 20, 1);
					break;
				case 2:
					item = make_shared<Money>(monster->getpoint(), 20, 1000);
					break;
				}

				if (item != nullptr)
				{
					gameobjects[ITEM].push_back(item);
				}
			}

			monster->setHP(HP);

			return false;
		}
	}

	return true;
}
