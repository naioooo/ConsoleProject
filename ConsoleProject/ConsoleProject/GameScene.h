#pragma once
#include "Scene.h"
#include "Player.h"
#include "Monster.h"

class GameScene :
    public Scene
{
public:
	static vector<vector<shared_ptr<Object>>> m_gameobjects;

private:
	shared_ptr<Player> m_player;
	vector<string> m_buffer;

	random_device m_rd;
	unsigned int m_generate_tick;

public:
	GameScene();
	GameScene(Player*& player);
	~GameScene();

	void loop() override;
	void draw() override;
	void input() override;
	void update();

	void generate_object();
	void generate_map();
	void generate_monster();
	void generate_item();

	bool collision_object(Point point);
};
