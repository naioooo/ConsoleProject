#pragma once
#include "GameScene.h"

int main()
{
	setconsole();

	float currentTime = GetTickCount64();
	float elapsedTime{};

	GameScene* gamescene = new GameScene();
	
	while (true)
	{
		if (tick(currentTime, elapsedTime))
		{
			gamescene->loop(elapsedTime);
		}
	}

	
}