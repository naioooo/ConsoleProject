#include "BossStage.h"
#include "GameScene.h"
#include "Item.h"
#include "HPUP.h"
#include "AttackUP.h"
#include "Money.h"
#include "SpeedUP.h"

void BossStage::Enter(int currentStageIndex)
{
	vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };

	gameObjects[PLAYER][0]->SetPoint(Point(MAX_WIDTH / 2 - 10, MAX_HEIGHT / 2));
	m_spawnTick = 250;
	GenerateObstacles(gameObjects);
	GenerateEnemies(gameObjects);
}

void BossStage::Update(float elapsedTime)
{
	vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };

	if (m_spawnTick > 300)
	{
		SpawnItems(gameObjects);
		m_spawnTick = 0;
	}

	m_spawnTick++;

	for (auto& objects : gameObjects)
	{
		for (auto& object : objects)
		{
			object->Update(elapsedTime);
		}
	}

	//죽은 개체는 벡터에서 삭제한다
	for (int i = MONSTER; i <= ITEM; i++)
	{
		auto newEnd = std::remove_if(gameObjects[i].begin(), gameObjects[i].end(), [](shared_ptr<Object>& obj)
			{
				return !obj->GetAlive();
			});

		gameObjects[i].erase(newEnd, gameObjects[i].end());
	}
}

void BossStage::Exit()
{
	vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };

	for (int i = 0; i < 3; i++)
	{
		gameObjects[i].clear();
		gameObjects[i].shrink_to_fit();
	}
}

bool BossStage::IsStageComplete(int level)
{
	vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };

	if (gameObjects[MONSTER].empty())
	{
		return true;
	}

	return false;
}

void BossStage::GenerateEnemies(vector<vector<shared_ptr<Object>>>& gameObjects)
{
	Point center{ MAX_WIDTH / 2 + 10 , MAX_HEIGHT / 2 };
	gameObjects[MONSTER].push_back(make_shared<BossMonster>(center, 3000, 180, 50, 50));
}

void BossStage::GenerateObstacles(vector<vector<shared_ptr<Object>>>& gameObjects)
{
	int x = 19;
	int y = 4;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			Point newPos = Point(x + i, y + j);

			gameObjects[OBSTACLE].push_back(make_shared<Object>(newPos));
		}
	}

	x = 39;
	y = 4;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Point newPos = Point(x + i, y + j);

			gameObjects[OBSTACLE].push_back(make_shared<Object>(newPos));
		}
	}

	x = 19;
	y = 14;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Point newPos = Point(x + i, y + j);

			gameObjects[OBSTACLE].push_back(make_shared<Object>(newPos));
		}
	}

	x = 39;
	y = 14;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Point newPos = Point(x + i, y + j);

			gameObjects[OBSTACLE].push_back(make_shared<Object>(newPos));
		}
	}

}

void BossStage::SpawnItems(vector<vector<shared_ptr<Object>>>& gameObjects)
{
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<int> width(0, MAX_WIDTH - 1);
	uniform_int_distribution<int> height(0, MAX_HEIGHT - 1);	
	uniform_int_distribution<int> rand(0, 3);

	Point newPos{};	 
	shared_ptr<Item> item;

	while (true)
	{
		newPos = Point{ width(gen), height(gen) };

		if (CollisionCheck(newPos, gameObjects))
		{
			break;
		}
	}

	switch (rand(gen))
	{
	case 0:
		item = make_shared<AttackUP>(newPos, 1000, 30);
		break;
	case 1:
		item = make_shared<HpUP>(newPos, 1000, 1);
		break;
	case 2:
		item = make_shared<Money>(newPos, 1000, 1000);
		break;
	case 3:
		item = make_shared<SpeedUP>(newPos, 1000, 10);
		break;
	}

	gameObjects[ITEM].push_back(item);
}

bool BossStage::CollisionCheck(Point point, vector<vector<shared_ptr<Object>>>& gameObjects)
{
	for (int i = 0; i < 4; i++)
	{
		for (auto& object : gameObjects[i])
		{
			if (object->GetPoint() == point)
			{
				return false;
			}
		}
	}

	return true;
}

