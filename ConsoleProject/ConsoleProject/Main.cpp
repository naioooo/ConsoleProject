#pragma once
#include "GameScene.h"

int main()
{
	system("title shooting game");
	system("mode con:cols=120 lines=28");

	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);

	DWORD currentTime = GetTickCount64();

	Point p;
	p.x = 10;
	p.y = 10;

	Player* player = new Player(p, 100, 10, 50, 50, "È£³¯µÎ");
	GameScene* gamescene = new GameScene(player);
	
	while (true)
	{
		if (tick(currentTime))
		{
			gamescene->loop();
		}
	}

	
}