#pragma once
#include "SceneManager.h"
#include "TimeManager.h"

int main()
{
	SetConsole();

	auto& sceneManager = SceneManager::Instance();

	FrameRateManager frame(60);
	float elapsedTime{};

	while (true)
	{
		if (frame.Tick(elapsedTime))
		{
			sceneManager.Update(elapsedTime);
		}
	}	
}