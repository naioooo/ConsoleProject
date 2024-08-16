#pragma once
#include "Scene.h"
#include "Player.h"
#include "Monster.h"
#include "StageManager.h"

class GameScene :
    public Scene
{
public:
	static vector<vector<shared_ptr<Object>>> m_gameobjects;

private:
	shared_ptr<Player> m_player;
	shared_ptr<StageManager> m_stagemanager;

	vector<string> m_buffer;

	random_device m_rd;
	unsigned int m_generate_tick;

public:
	GameScene();
	~GameScene();

	void loop(float elapsedTime) override;
	void draw() override;
	void input() override;
	void update(float elapsedTime);

	void draw_UI();

};
