#pragma once
#include "GameScene.h"

int main()
{
	setconsole();

	DWORD currentTime = GetTickCount64();

	GameScene* gamescene = new GameScene();
	
	while (true)
	{
		if (tick(currentTime))
		{
			gamescene->loop();
		}
	}

	
}