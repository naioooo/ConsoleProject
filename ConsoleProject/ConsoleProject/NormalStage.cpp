#include "NormalStage.h"
#include "GameScene.h"

void NormalStage::Enter(int currentStageIndex)
{
	vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };

	m_level = currentStageIndex + 1;
	m_spawnTick = 250;
	gameObjects[PLAYER][0]->SetPoint(Point(MAX_WIDTH / 2, MAX_HEIGHT / 2));
	GenerateObstacles(gameObjects);
}

void NormalStage::Update(float elapsedTime)
{
	vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };
	
	if (m_spawnTick > 300)
	{
		SpawnEnemies(gameObjects);
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

void NormalStage::Exit()
{
	vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };

	for (int i = 0; i < 3; i++)
	{
		gameObjects[i].clear();
		gameObjects[i].shrink_to_fit();
	}
	shared_ptr<Player> player = dynamic_pointer_cast<Player> (gameObjects[PLAYER][0]);

	player->ClearBullets();
}

void NormalStage::SpawnEnemies(vector<vector<shared_ptr<Object>>>& gameObjects)
{	
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<int> width(0, MAX_WIDTH - 1);
	uniform_int_distribution<int> height(0, MAX_HEIGHT - 1);
	uniform_int_distribution<int> edges(0, 3);

	int cnt = 0;

	while (true)
	{
		if (cnt >= 5)
			break;

		int edge = edges(gen); // 0-왼쪽, 1-오른쪽, 2-위쪽, 3-아래쪽
		Point newPos{};
		if (edge == 0) 
		{ // 왼쪽 끝
			newPos = Point(0, height(gen));
		}
		else if (edge == 1) 
		{ // 오른쪽 끝
			newPos = Point(MAX_WIDTH - 1, height(gen));
		}
		else if (edge == 2)
		{ // 위쪽 끝
			newPos = Point(width(gen), 0);
		}
		else if (edge == 3)
		{ // 아래쪽 끝
			newPos = Point(width(gen), MAX_HEIGHT - 1);
		}

		if (CollisionCheck(newPos, gameObjects))
		{
			gameObjects[MONSTER].push_back(make_shared<Monster>(newPos, 50 * m_level, 500, 1, 50));
			cnt++;
		}
	}
}

void NormalStage::GenerateObstacles(vector<vector<shared_ptr<Object>>>& gameObjects)
{	
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<int> width(0, MAX_WIDTH - 1);
	uniform_int_distribution<int> height(0, MAX_HEIGHT - 1);

	int cnt = 0;

	while (true)
	{
		if (cnt > 50)
			break;

		Point newPos = Point(width(gen), height(gen));


		if (CollisionCheck(newPos, gameObjects))
		{
			gameObjects[OBSTACLE].push_back(make_shared<Object>(newPos));
			cnt++;
		}
	}
}

bool NormalStage::CollisionCheck(Point point, vector<vector<shared_ptr<Object>>>& gameObjects)
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

bool NormalStage::IsStageComplete(int level)
{
	vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };
	shared_ptr<Player> player = dynamic_pointer_cast<Player> (gameObjects[PLAYER][0]);
	
	if (player->GetKillCnt() >= level * 10)
	{
		player->SetKillCnt(0);
		return true;
	}

	return false;
}
