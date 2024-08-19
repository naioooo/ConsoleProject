#pragma once
#include "Scene.h"
#include "Player.h"
#include "Monster.h"
#include "BossMonster.h"
#include "StageManager.h"
#include "SceneManager.h"

class GameScene :
    public Scene
{
public:
	static vector<vector<shared_ptr<Object>>> m_gameobjects;

private:
	vector<string> m_buffer;
	shared_ptr<Player> m_player;
	shared_ptr<StageManager> m_stageManager;

public:
	GameScene();
	~GameScene();

	void Enter() override;
	void Exit() override;

	void Update(float elapsedTime) override;
	void Draw() override;
	void DrawUI();
	void Input() override;
	void ChangeScene() override; // 조건 체크 메서드


};
