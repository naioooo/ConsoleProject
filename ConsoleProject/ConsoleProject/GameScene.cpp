#pragma once
#include "GameScene.h"

vector<vector<shared_ptr<Object>>> GameScene::m_gameobjects{};

GameScene::GameScene()
{
	string str;
	str.resize(MAX_WIDTH, ' ');

	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		m_buffer.push_back(str);
	}

	m_generate_tick = 0;

	m_gameobjects.resize(4);
	m_gameobjects[PLAYER].push_back(make_shared <Player>(Point(10, 10), 30, 1, 50, 50, "호날두"));
	m_player = dynamic_pointer_cast<Player>(m_gameobjects[PLAYER][0]);

	draw_UI();

	m_stagemanager = make_shared<StageManager>();
	m_stagemanager->EnterStage();
}

GameScene::~GameScene()
{
}

void GameScene::loop(float elapsedTime)
{
	input();
	m_stagemanager->UpdateStage(elapsedTime);
	//update(elapsedTime);
	draw();
}

void GameScene::draw()
{
	// 버퍼를 초기화 후 오브젝트를 넣는다
	for (auto& buf : m_buffer)
	{
		buf.clear();
		buf.resize(MAX_WIDTH, ' ');
	}

	for (auto& objects : m_gameobjects)
	{
		for (auto& object : objects)
		{
			if (object->getalive())
			{
				object->insertbuffer(m_buffer);
			}
		}
	}

	// 게임화면
	int x = 5;
	int y = 5;
	string str;
	gotoxy(x, y);

	for (const auto& str : m_buffer)
	{
		for (const auto& ch : str)
		{
			switch (ch)
			{
			case CH_OBSTACLE:
				textcolor(WHITE);
				break;
			case CH_MONSTER1:
			case CH_MONSTER2:
			case CH_MONSTER3:
				textcolor(DarkRed);
				break;
			case CH_PLAYER:
				textcolor(BLUE);
				break;
			case CH_BULLET:
				textcolor(DarkYellow);
				break;
			case CH_HPUP:
				textcolor(RED);
				break;
			case CH_MONEY:
				textcolor(YELLOW);
				break;
			case CH_ATTACKUP:
				textcolor(PURPLE);
				break;
			}

			cout << ch;
			textcolor(BLACK);
		}
		gotoxy(x, ++y);
	}		

	// 게임 정보 출력
	x = 72;
	y = 6;
	gotoxy(x, y);

	textcolor(RED);
	cout << "HP : ";
	for (int i = 0; i < 30; i++)
	{
		if (i < m_player->getHP())
		{
			cout << "▒";
		}
		else
		{
			cout << " ";
		}
	}

	y++;
	gotoxy(x, y);
	textcolor(YELLOW);
	cout << "MONEY : "; 
	str = to_string(m_player->getmoney());
	for (int i = 0; i < 5; i++)
	{
		if (i < str.length())
		{
			cout << str[i];
		}
		else
		{
			cout << " ";
		}
	}

	y++;
	gotoxy(x, y);
	textcolor(YELLOW);
	cout << "ATTACK : ";
	str = to_string(m_player->getattack());
	for (int i = 0; i < 4; i++)
	{
		if (i < str.length())
		{
			cout << str[i];
		}
		else
		{
			cout << " ";
		}
	}

	y++;
	gotoxy(x, y);
	textcolor(YELLOW);

	cout << "KILL COUNT : ";
	str = to_string(m_player->getkill_cnt());
	for (int i = 0; i < 2; i++)
	{
		if (i < str.length())
		{
			cout << str[i];
		}
		else
		{
			cout << " ";
		}
	}
	cout << " / " << (m_stagemanager->getcurrentStageIndex() + 1) * 10;

	


	/////////
	x = 72;
	y = 19;
	gotoxy(x, y);
	cout << "skill : ";


	x += 8;
	gotoxy(x, y);
	textcolor(YELLOW);
	cout << " 회복";

	x += 9;
	gotoxy(x, y);
	textcolor(YELLOW);
	cout << " 흩뿌리기";

	x += 12;
	gotoxy(x, y);
	textcolor(YELLOW);
	cout << " 레이저";

	//

	x = 72;
	y = 20;
	gotoxy(x, y);
	cout << "cost  : ";

	x += 8;
	gotoxy(x, y);
	textcolor(YELLOW);
	cout << " 500 ";

	x += 9;
	gotoxy(x, y);
	textcolor(YELLOW);
	cout << " 1000";

	x += 12;
	gotoxy(x, y);
	textcolor(YELLOW);
	cout << " 1000";

	/////////
	x = 72;
	y = 21;
	gotoxy(x, y);
	cout << "count : ";

	x += 9;
	gotoxy(x, y);
	str = to_string(m_player->getskill_cnt()[0]);
	for (int i = 0; i < 2; i++)
	{
		if (i < str.length())
		{
			cout << str[i];
		}
		else
		{
			cout << " ";
		}
	}

	x += 9;
	gotoxy(x, y);
	str = to_string(m_player->getskill_cnt()[1]);
	for (int i = 0; i < 2; i++)
	{
		if (i < str.length())
		{
			cout << str[i];
		}
		else
		{
			cout << " ";
		}
	}

	x += 12;
	gotoxy(x, y);
	str = to_string(m_player->getskill_cnt()[2]);
	for (int i = 0; i < 2; i++)
	{
		if (i < str.length())
		{
			cout << str[i];
		}
		else
		{
			cout << " ";
		}
	}
}

void GameScene::draw_UI()
{
	string s1 = "┌";
	string s2 = "┐";
	string s3 = "└";
	string s4 = "┘";
	string s5 = "─";
	string s6 = "│";

	int x = 50;
	int y = 2;
	gotoxy(x, y);

	cout << " SHOOTING GAME" << endl;


	x = 4;
	y = 4;
	int width = MAX_WIDTH;
	int height = MAX_HEIGHT;

	textcolor(WHITE);

	gotoxy(x, y);
	cout << s1;
	for (int i = 0; i < width; i++)
	{
		cout << s5;
	}
	cout << s2;

	for (int i = 1; i <= height; i++)
	{
		gotoxy(x, y + i);
		cout << s6;
		for (int j = 0; j < width; j++)
		{
			cout << " ";
		}
		cout << s6 ;
	}

	gotoxy(x, y + height + 1);
	cout << s3;
	for (int i = 0; i < width; i++)
	{
		cout << s5;
	}
	cout << s4;

	///////////////////////////////////////////////////////////////////////
	
	x = 70; y = 4;
	width = 45; height = 20;

	gotoxy(x, y);
	cout << s1;
	for (int i = 0; i < width; i++)
	{
		cout << s5;
	}
	cout << s2;

	for (int i = 1; i <= height; i++)
	{
		gotoxy(x, y + i);
		cout << s6;
		for (int j = 0; j < width; j++)
		{
			cout << " ";
		}
		cout << s6;
	}

	gotoxy(x, y + height + 1);
	cout << s3;
	for (int i = 0; i < width; i++)
	{
		cout << s5;
	}
	cout << s4;
	
}

void GameScene::input()
{
	m_player->input();
}

void GameScene::update(float elapsedTime)
{
}


