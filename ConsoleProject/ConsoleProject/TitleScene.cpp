#include "TitleScene.h"

TitleScene::TitleScene()
{
	m_check = false;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Enter()
{
	m_check = false;
	Draw();
}

void TitleScene::Exit()
{
	system("cls");
}

void TitleScene::Update(float elapsedTime)
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8001)
	{
		m_check = true;
	}

	ChangeScene();
}

void TitleScene::Draw()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PURPLE | (PURPLE << 4));
	string str = "11 4,12 4,13 4,16 4,20 4,23 4,24 4,25 4,26 4,30 4,31 4,32 4,33 4,36 4,37 4,38 4,39 4,40 4,42 4,44 4,45 4,49 4,52 4,53 4,54 4,55 4,61 4,62 4,63 4,64 4,69 4,73 4,74 4,79 4,80 4,82 4,83 4,84 4,85 4,91 4,92 4,93 4,94 4,98 4,99 4,100 4,105 4,106 4,107 4,108 4,111 4,112 4,113 4,114 4,10 5,13 5,16 5,20 5,22 5,23 5,27 5,29 5,30 5,34 5,38 5,42 5,44 5,45 5,49 5,51 5,52 5,60 5,61 5,65 5,68 5,69 5,73 5,74 5,79 5,80 5,82 5,90 5,94 5,97 5,101 5,104 5,108 5,111 5,115 5,11 6,16 6,20 6,22 6,27 6,29 6,34 6,38 6,42 6,44 6,46 6,49 6,51 6,60 6,68 6,70 6,73 6,75 6,78 6,80 6,82 6,90 6,96 6,101 6,102 6,103 6,104 6,110 6,115 6,12 7,13 7,16 7,17 7,18 7,19 7,20 7,22 7,27 7,29 7,34 7,38 7,42 7,44 7,46 7,47 7,49 7,51 7,54 7,55 7,60 7,63 7,64 7,65 7,67 7,70 7,73 7,75 7,78 7,80 7,82 7,83 7,84 7,85 7,89 7,90 7,92 7,93 7,94 7,96 7,102 7,103 7,106 7,107 7,108 7,110 7,115 7,13 8,14 8,16 8,20 8,22 8,27 8,29 8,34 8,38 8,42 8,44 8,47 8,49 8,51 8,55 8,60 8,65 8,67 8,68 8,69 8,70 8,71 8,73 8,75 8,76 8,77 8,80 8,82 8,90 8,94 8,96 8,101 8,102 8,103 8,104 8,108 8,110 8,115 8,10 9,13 9,14 9,16 9,20 9,22 9,23 9,26 9,27 9,29 9,30 9,33 9,34 9,38 9,42 9,44 9,48 9,49 9,51 9,52 9,55 9,60 9,61 9,65 9,67 9,71 9,73 9,76 9,77 9,80 9,82 9,90 9,94 9,97 9,101 9,104 9,108 9,110 9,111 9,115 9,11 10,12 10,13 10,16 10,20 10,23 10,24 10,25 10,26 10,30 10,31 10,32 10,33 10,38 10,42 10,44 10,48 10,49 10,52 10,53 10,54 10,55 10,61 10,62 10,63 10,64 10,66 10,71 10,73 10,76 10,77 10,80 10,82 10,83 10,84 10,85 10,91 10,92 10,93 10,94 10,97 10,98 10,99 10,100 10,105 10,106 10,107 10,108 10,111 10,112 10,113 10,114 10,40 19,41 19,42 19,43 19,44 19,46 19,47 19,48 19,50 19,51 19,52 19,53 19,55 19,56 19,57 19,58 19,60 19,61 19,62 19,66 19,67 19,68 19,69 19,70 19,71 19,72 19,73 19,74 19,76 19,77 19,78 19,79 19,82 19,83 19,84 19,86 19,87 19,88 19,89 19,40 20,41 20,44 20,46 20,47 20,50 20,53 20,55 20,59 20,60 20,66 20,70 20,71 20,74 20,79 20,81 20,82 20,86 20,89 20,40 21,41 21,44 21,46 21,47 21,50 21,51 21,52 21,53 21,56 21,57 21,60 21,61 21,62 21,67 21,68 21,70 21,71 21,74 21,76 21,77 21,78 21,79 21,81 21,82 21,86 21,87 21,88 21,89 21,40 22,41 22,44 22,46 22,47 22,50 22,57 22,58 22,62 22,68 22,69 22,70 22,71 22,74 22,76 22,79 22,81 22,82 22,84 22,86 22,40 23,41 23,42 23,43 23,44 23,46 23,47 23,50 23,51 23,52 23,53 23,55 23,56 23,57 23,59 23,60 23,61 23,62 23,66 23,67 23,68 23,70 23,71 23,72 23,73 23,74 23,76 23,77 23,78 23,79 23,82 23,83 23,84 23,86 23,87 23,88 23,89 23,40 24,41 24,70 24,71 24,40 25,41 25,70 25,71 25";
	int start = 0;
	int end = 0;
	int x = 0;
	int y = 0;
	while (true)
	{
		if (str.length() < end)
			break;

		if (str[end] == ' ')
		{
			x = stoi(str.substr(start, end - start));
			start = end + 1;
		}
		else if (str[end] == ',')
		{
			y = stoi(str.substr(start, end - start));
			start = end + 1;

			gotoxy(x - 4, y);
			cout << "��";
		}

		end++;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE | (BLACK << 4));
}

void TitleScene::Input()
{
}

void TitleScene::ChangeScene()
{
	if (m_check == true)
	{
		SceneManager::Instance().ChangeScene("Game");
	}
}


