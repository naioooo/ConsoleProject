#pragma once
#include "Scene.h"
#include "SceneManager.h"

class EndingScene :
    public Scene
{
private:
	bool m_check;

public:
	EndingScene();
	~EndingScene();

	void Enter() override;
	void Exit() override;

	void Update(float elapsedTime) override;
	void Draw() override;
	void Input() override;
	void ChangeScene() override; // 조건 체크 메서드
};

