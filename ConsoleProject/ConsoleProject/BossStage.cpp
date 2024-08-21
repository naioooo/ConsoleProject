#include "BossStage.h"
#include "GameScene.h"

void BossStage::Enter()
{
	vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };

	gameObjects[PLAYER][0]->SetPoint(Point(MAX_WIDTH / 2 - 10, MAX_HEIGHT / 2));
	GenerateObstacles(gameObjects);
	GenerateEnemies(gameObjects);
}

void BossStage::Update(float elapsedTime)
{
	vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };

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
	gameObjects[MONSTER].push_back(make_shared<BossMonster>(center, 30, 180, 50, 50));
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

bool BossStage::CollisionCheck(Point point, vector<vector<shared_ptr<Object>>>& gameObjects)
{
	return false;
}

