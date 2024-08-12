#pragma once
#include "Scene.h"
#include "Player.h"
#include "Monster.h"

class GameScene :
    public Scene
{
	vector<string> m_buffer;

	Player* m_player;
	vector<Monster*> m_monsters;

public:
	GameScene();
	GameScene(Player*& player);
	~GameScene();

	void loop();
	void draw();
	void input();
	void update();
};

