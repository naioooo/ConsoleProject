#include "Bullet.h"
#include "GameScene.h"
#include "Item.h"
#include "HPUP.h"
#include "AttackUP.h"
#include "Money.h"
#include "SpeedUP.h"

Bullet::Bullet()
{
}

Bullet::Bullet(const Point point, const int speed, const int dir, const int damage, const int lifetime)
	: Projectile(point, speed, dir, damage, lifetime)
{
}

Bullet::~Bullet()
{
}

void Bullet::InsertBuffer(vector<string>& buffer)
{
    buffer[m_point.y][m_point.x] = CH_BULLET;
}

bool Bullet::CollisionCheck(Point point)
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

	for (auto& object : gameObjects[MONSTER])
	{
		if (gameObjects[MONSTER].size() == 1)
		{
			shared_ptr<BossMonster> bossmonster = dynamic_pointer_cast<BossMonster>(object);
			if (bossmonster != nullptr)
			{
				Point pos = bossmonster->GetPoint();

				if (point.x >= pos.x - 1 && point.x <= pos.x + 1 && point.y >= pos.y - 1 && point.y <= pos.y + 1)
				{
					int HP = bossmonster->GetHP() - m_damage;
					bossmonster->SetHP(HP);

					return false;
				}
			}
		}
		if (object->GetPoint() == point)
		{
			shared_ptr<Monster> monster = dynamic_pointer_cast<Monster>(object);
			int HP = monster->GetHP() - m_damage;
			if (HP <= 0)
			{
				vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };

				shared_ptr<Player> player = dynamic_pointer_cast<Player>(gameObjects[PLAYER][0]);
				player->SetKillCnt(player->GetKillCnt() + 1);

				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<int> rand(0, 5);

				shared_ptr<Item> item;

				switch (rand(gen))
				{
				case 0:
					item = make_shared<AttackUP>(monster->GetPoint(), 1000, 30);
					break;
				case 1:
					item = make_shared<HpUP>(monster->GetPoint(), 1000, 1);
					break;
				case 2:
					item = make_shared<Money>(monster->GetPoint(), 1000, 1000);
					break;
				case 3:
					item = make_shared<SpeedUP>(monster->GetPoint(), 1000, 10);
					break;
				}

				if (item != nullptr)
				{
					gameObjects[ITEM].push_back(item);
				}
			}

			monster->SetHP(HP);

			return false;
		}
	}

	return true;
}
