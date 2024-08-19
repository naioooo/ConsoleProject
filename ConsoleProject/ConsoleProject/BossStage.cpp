#include "BossStage.h"
#include "GameScene.h"

void BossStage::Enter()
{
	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

	gameobjects[PLAYER][0]->SetPoint(Point(MAX_WIDTH / 2 - 10, MAX_HEIGHT / 2));
	GenerateObstacles(gameobjects);
	GenerateEnemies(gameobjects);
}

void BossStage::Update(float elapsedTime)
{
	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

	for (auto& objects : gameobjects)
	{
		for (auto& object : objects)
		{
			object->Update(elapsedTime);
		}
	}

	//죽은 개체는 벡터에서 삭제한다
	for (int i = MONSTER; i <= ITEM; i++)
	{
		auto newEnd = std::remove_if(gameobjects[i].begin(), gameobjects[i].end(), [](shared_ptr<Object>& obj)
			{
				return !obj->GetAlive();
			});

		gameobjects[i].erase(newEnd, gameobjects[i].end());
	}
}

void BossStage::Exit()
{
	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

	for (int i = 0; i < 3; i++)
	{
		gameobjects[i].clear();
		gameobjects[i].shrink_to_fit();
	}
}

bool BossStage::IsStageComplete(int level)
{
	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

	if (gameobjects[MONSTER].empty())
	{
		return true;
	}

	return false;
}

void BossStage::GenerateEnemies(vector<vector<shared_ptr<Object>>>& gameobjects)
{
	Point center{ MAX_WIDTH / 2 + 10 , MAX_HEIGHT / 2 };
	gameobjects[MONSTER].push_back(make_shared<BossMonster>(center, 30, 180, 50, 50));
}

void BossStage::GenerateObstacles(vector<vector<shared_ptr<Object>>>& gameobjects)
{
	int x = 19;
	int y = 4;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			Point newPos = Point(x + i, y + j);

			gameobjects[OBSTACLE].push_back(make_shared<Object>(newPos));
		}
	}

	x = 39;
	y = 4;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Point newPos = Point(x + i, y + j);

			gameobjects[OBSTACLE].push_back(make_shared<Object>(newPos));
		}
	}

	x = 19;
	y = 14;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Point newPos = Point(x + i, y + j);

			gameobjects[OBSTACLE].push_back(make_shared<Object>(newPos));
		}
	}

	x = 39;
	y = 14;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Point newPos = Point(x + i, y + j);

			gameobjects[OBSTACLE].push_back(make_shared<Object>(newPos));
		}
	}

}

bool BossStage::CollisionCheck(Point point, vector<vector<shared_ptr<Object>>>& gameobjects)
{
	return false;
}

