#pragma once
#include "library.h"

class Scene
{
private:



public:
	Scene();
	~Scene() = default;

	virtual void Update(float elapsedTime) = 0;
	virtual void Draw() = 0;
	virtual void Input(float elapsedTime) = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void ChangeScene() = 0; // 조건 체크 메서드
};

