#pragma once
#include "GameScene.h"

GameScene::GameScene()
{
	
}

GameScene::GameScene(Player* &player)
{
	string str;
	str.resize(MAX_WIDTH, ' ');

	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		m_buffer.push_back(str);
	}

	Point p;
	p.x = 1;
	p.y = 1;
	m_monsters.push_back(new Monster(p, 100, 10, 50, 50));

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
	m_player->move();
}

void GameScene::update()
{
	for (auto& monster : m_monsters)
	{
		monster->update();
	}

	for (auto& buf : m_buffer)
	{
		buf.clear();
		buf.resize(MAX_WIDTH, ' ');
	}

	m_player->insertbuffer(m_buffer);
	for (auto& monster : m_monsters)
	{
		monster->insertbuffer(m_buffer);
	}
}

