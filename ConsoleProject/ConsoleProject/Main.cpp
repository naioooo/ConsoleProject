#pragma once
#include "SceneManager.h"

int main()
{
	setconsole();

	float currentTime = GetTickCount64();
	float elapsedTime{};

	auto& sceneManager = SceneManager::Instance();

	sceneManager.AddScene("Title", std::make_shared<TitleScene>());
	sceneManager.AddScene("Game", std::make_shared<GameScene>());
	sceneManager.AddScene("Ending", std::make_shared<EndingScene>());
	
	sceneManager.ChangeScene("Title");

	while (true)
	{
		if (tick(currentTime, elapsedTime))
		{
			sceneManager.Update(elapsedTime);
		}
	}	
}