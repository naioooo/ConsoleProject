#include "NormalStage.h"
#include "GameScene.h"

void NormalStage::Enter()
{
	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

	m_spawn_tick = 0;
	GenerateObstacles(gameobjects);
}

void NormalStage::Update(float elapsedTime)
{
	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

	if (m_spawn_tick > 10)
	{
		SpawnEnemies(gameobjects);
		m_spawn_tick = 0;
	}

	m_spawn_tick++;

	for (auto& objects : gameobjects)
	{
		for (auto& object : objects)
		{
			object->update(elapsedTime);
		}
	}

	//죽은 개체는 벡터에서 삭제한다
	for (auto& objects : gameobjects)
	{
		auto newEnd = std::remove_if(objects.begin(), objects.end(), [](shared_ptr<Object>& obj)
			{
				return !obj->getalive();
			});

		objects.erase(newEnd, objects.end());
	}
}

void NormalStage::Exit()
{
	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };

	for (int i = 0; i < 3; i++)
	{
		gameobjects[i].clear();
		gameobjects[i].shrink_to_fit();
	}
}

void NormalStage::SpawnEnemies(vector<vector<shared_ptr<Object>>>& gameobjects)
{	
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<int> width(0, MAX_WIDTH - 1);
	uniform_int_distribution<int> height(0, MAX_HEIGHT - 1);
	uniform_int_distribution<int> edges(0, 4);

	int cnt = 0;

	while (true)
	{
		if (cnt >= 1)
			break;

		int edge = edges(gen); // 0-왼쪽, 1-오른쪽, 2-위쪽, 3-아래쪽
		Point new_pos{};
		if (edge == 0) { // 왼쪽 끝
			new_pos = Point(0, height(gen));
		}
		else if (edge == 1) { // 오른쪽 끝
			new_pos = Point(MAX_WIDTH - 1, height(gen));
		}
		else if (edge == 2) { // 위쪽 끝
			new_pos = Point(width(gen), 0);
		}
		else if (edge == 3) { // 아래쪽 끝
			new_pos = Point(width(gen), MAX_HEIGHT - 1);
		}

		if (CollisionObject(new_pos, gameobjects))
		{
			gameobjects[MONSTER].push_back(make_shared<Monster>(new_pos, 1, 180, 50, 50));
			cnt++;
		}
	}
}

void NormalStage::GenerateObstacles(vector<vector<shared_ptr<Object>>>& gameobjects)
{	
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<int> width(0, MAX_WIDTH - 1);
	uniform_int_distribution<int> height(0, MAX_HEIGHT - 1);

	int cnt = 0;
	int i = 5;

	while (true)
	{
		if (cnt > 50)
			break;

		Point new_pos = Point(width(gen), height(gen));


		if (CollisionObject(new_pos, gameobjects))
		{
			gameobjects[OBSTACLE].push_back(make_shared<Object>(new_pos));
			cnt++;
		}
	}
}

bool NormalStage::CollisionObject(Point point, vector<vector<shared_ptr<Object>>>& gameobjects)
{	
	for (int i = 0; i < 4; i++)
	{
		for (auto& object : gameobjects[i])
		{
			if (object->getpoint() == point)
			{
				return false;
			}
		}
	}

	return true;
}

bool NormalStage::IsStageComplete(int level)
{
	vector<vector<shared_ptr<Object>>>& gameobjects{ GameScene::m_gameobjects };
	shared_ptr<Player> player = dynamic_pointer_cast<Player> (gameobjects[PLAYER][0]);
	
	if (player->getkill_cnt() >= level * 10)
	{
		player->setkill_cnt(0);
		return true;
	}

	return false;
}
