#pragma once
#include "SceneManager.h"
#include "TimeManager.h"

int main()
{
	SetConsole();

	auto& sceneManager = SceneManager::Instance();

	sceneManager.AddScene("Title", std::make_shared<TitleScene>());
	sceneManager.AddScene("Game", std::make_shared<GameScene>());
	sceneManager.AddScene("Ending", std::make_shared<EndingScene>());
	
	sceneManager.ChangeScene("Title");

	const int fps = 60; // ∏Ò«• FPS
	FrameRateManager frame(fps);
	float elapsedTime{};

	while (true)
	{
		if (frame.tick(elapsedTime))
		{
			sceneManager.Update(elapsedTime);
		}
	}	
}