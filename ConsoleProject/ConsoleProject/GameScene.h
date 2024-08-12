#pragma once
#include "Scene.h"
#include "Player.h"
#include "Monster.h"

class GameScene :
    public Scene
{
private:
	vector<string> m_buffer;

	Player* m_player;
	vector<Monster*> m_monsters;
	vector<Object*> m_obstacles;

	random_device rd;

	unsigned int m_generate_tick;

public:
	GameScene();
	GameScene(Player*& player);
	~GameScene();

	static vector<vector<Object*>> m_gameobjects;

	void loop();
	void draw();
	void input();
	void update();

	void generate_object();
	void generate_map();
	void generate_monster();
	void generate_item();

	bool collision_check(Object*& a, Object*& b);

};

