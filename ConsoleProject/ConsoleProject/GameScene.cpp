#pragma once
#include "GameScene.h"

GameScene::GameScene()
{
	m_player = new Player(Point(10, 10), 100, 1, 50, 50, "호날두");

	string str;
	str.resize(MAX_WIDTH, ' ');

	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		m_buffer.push_back(str);
	}

	m_generate_tick = 0;
	generate_map();
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

	m_player = player;


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

	for (const auto& buf : m_buffer)
	{
		cout << buf << endl;
	}		
}

void GameScene::input()
{
	m_player->move(m_gameobjects);
}

void GameScene::update()
{
	//오브젝트를 생성한다
	//generate_object();

	//오브젝트 업데이트
	for (auto& monster : m_monsters)
	{
		monster->update();
	}

	
	// 몬스터는 장애물과 플레이어 충돌체크
	// 플레이어는 장애물과 몬스터 아이템 충돌체크




	// 버퍼에 오브젝트를 넣는다

	for (auto& buf : m_buffer)
	{
		buf.clear();
		buf.resize(MAX_WIDTH, ' ');
	}

	for (auto& obstacle : m_obstacles)
	{
		obstacle->insertbuffer(m_buffer);
	}
	for (auto& monster : m_monsters)
	{
		monster->insertbuffer(m_buffer);
	}
	m_player->insertbuffer(m_buffer);
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
	mt19937 gen(rd());

	uniform_int_distribution<int> width(0, MAX_WIDTH - 1);
	uniform_int_distribution<int> height(0, MAX_HEIGHT - 1);

	for (int i = 0; i < 10; i++)
	{
		m_obstacles.push_back(new Object(Point(width(gen), height(gen))));
	}
}

void GameScene::generate_monster()
{
	mt19937 gen(rd());

	uniform_int_distribution<int> width(0, MAX_WIDTH - 1);
	uniform_int_distribution<int> height(0, MAX_HEIGHT - 1);
	
	m_monsters.push_back(new Monster(Point(width(gen), height(gen)), 100, 10, 50, 50));
}

void GameScene::generate_item()
{


}

bool GameScene::collision_check(Object*& a, Object*& b)
{
	if (a->getpoint().x == b->getpoint().x && a->getpoint().y == b->getpoint().y)
		return true;

	return false;
}



