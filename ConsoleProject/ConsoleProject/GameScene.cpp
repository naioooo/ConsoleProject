#pragma once
#include "GameScene.h"

vector<vector<shared_ptr<Object>>> GameScene::m_gameobjects{};

GameScene::GameScene()
{
	m_gameobjects.resize(5);

	string str;
	str.resize(MAX_WIDTH, ' ');

	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		m_buffer.push_back(str);
	}

	m_generate_tick = 0;
	generate_map();

	m_gameobjects[PLAYER].push_back(make_shared <Player>(Point(10, 10), 100, 1, 50, 50, "호날두"));
	m_player = dynamic_pointer_cast<Player>(m_gameobjects[PLAYER][0]);

	generate_monster();
}

GameScene::GameScene(Player* &player)
{
	string str;
	str.resize(MAX_WIDTH, ' ');

	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		m_buffer.push_back(str);
	}
	m_generate_tick = 0;
}

GameScene::~GameScene()
{
}

void GameScene::loop()
{
	input();
	update();	
	draw();
}

void GameScene::draw()
{
	gotoxy(0, 0);

	for (const auto& str : m_buffer)
	{
		for (const auto& ch : str)
		{
			switch (ch)
			{
			case '#':
				textcolor(WHITE);
				break;
			case '!':
				textcolor(RED);
				break;
			case '@':
				textcolor(BLUE);
				break;
			}

			cout << ch;
			textcolor(BLACK);
		}
		cout << endl;
	}		
}

void GameScene::input()
{
	m_player->move();
}

void GameScene::update()
{
	//오브젝트를 생성한다
	//generate_object();
		
	for (auto& objects : m_gameobjects)
	{
		for (auto& object : objects)
		{
			object->update();
		}
	}
	
	// 버퍼를 초기화 후 오브젝트를 넣는다
	for (auto& buf : m_buffer)
	{
		buf.clear();
		buf.resize(MAX_WIDTH, ' ');
	}

	for (auto& objects : m_gameobjects)
	{
		for (auto& object : objects)
		{
			object->insertbuffer(m_buffer);
		}
	}
}

void GameScene::generate_object()
{
	if (m_generate_tick > 10)
	{
		generate_monster();
		m_generate_tick = 0;
	}

	m_generate_tick++;
}

void GameScene::generate_map()
{
	mt19937 gen(m_rd());

	uniform_int_distribution<int> width(0, MAX_WIDTH - 1);
	uniform_int_distribution<int> height(0, MAX_HEIGHT - 1);

	int cnt = 0;

	while (true)
	{
		if (cnt > 20)
			break;

		Point new_pos = Point(width(gen), height(gen));

		if (collision_object(new_pos))
		{
			m_gameobjects[OBSTACLE].push_back(make_shared<Object>(new_pos));
			cnt++;
		}
	}
}

void GameScene::generate_monster()
{
	mt19937 gen(m_rd());
		
	uniform_int_distribution<int> width(0, MAX_WIDTH - 1);
	uniform_int_distribution<int> height(0, MAX_HEIGHT - 1);
	
	int cnt = 0;

	while (true)
	{
		if (cnt > 10)
			break;

		Point new_pos = Point(width(gen), height(gen));

		if (collision_object(new_pos))
		{
			m_gameobjects[MONSTER].push_back(make_shared<Monster>(new_pos, 100, 10, 50, 50));
			cnt++;
		}
	}
	
}

void GameScene::generate_item()
{


}

bool GameScene::collision_object(Point point)
{
	for (int i = 0; i < 5; i++)
	{
		for (auto& object : m_gameobjects[i])
		{
			if (object->getpoint() == point)
			{
				return false;
			}
		}
	}

	return true;
}



