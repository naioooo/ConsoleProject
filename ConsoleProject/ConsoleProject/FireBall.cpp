#include "fireBall.h"
#include "GameScene.h"

FireBall::FireBall()
{
}

FireBall::FireBall(const Point point, const int speed, const int dir, const int damage, const int lifetime)
	: Projectile(point, speed, dir, damage, lifetime)
{
}

FireBall::~FireBall()
{
}

void FireBall::InsertBuffer(vector<string>& buffer)
{
	buffer[m_point.y][m_point.x] = CH_FIREBALL;
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
		if (!player->GetInvincibility())
		{
			player->SetHP(HP);
		}
		return false;
	}
	
	return true;
}
