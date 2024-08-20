#pragma once
#include "GameScene.h"

vector<vector<shared_ptr<Object>>> GameScene::m_gameobjects{};

GameScene::GameScene()
{	
}

GameScene::~GameScene()
{
}

void GameScene::Enter()
{
	string str;
	str.resize(MAX_WIDTH, ' ');

	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		m_buffer.push_back(str);
	}

	m_gameobjects.resize(4);
	m_gameobjects[PLAYER].push_back(make_shared <Player>(Point(MAX_WIDTH / 2, MAX_HEIGHT / 2), 30, 1, 50, 50, "호날두"));
	m_player = dynamic_pointer_cast<Player>(m_gameobjects[PLAYER][0]);

	DrawUI();

	m_stageManager = make_shared<StageManager>();
	m_stageManager->EnterStage();
}

void GameScene::Exit()
{
	system("cls");

	for (auto& buf : m_buffer)
	{
		buf.clear();
		buf.shrink_to_fit();
	}
	m_buffer.clear();
	m_buffer.shrink_to_fit();

	for (auto& object : m_gameobjects)
	{
		object.clear();
		object.shrink_to_fit();
	}
	m_gameobjects.clear();
	m_gameobjects.shrink_to_fit();

	m_stageManager = nullptr;
}

void GameScene::Update(float elapsedTime)
{
	Input();
	m_stageManager->UpdateStage(elapsedTime);
	Draw();
	ChangeScene();
}

void GameScene::Draw()
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
			if (object->GetAlive())
			{
				object->InsertBuffer(m_buffer);
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
			case CH_FIREBALL:
				textcolor(RED);
				break;
			case CH_MONSTER1:
			case CH_MONSTER2:
			case CH_MONSTER3:
				textcolor(DarkRed);
				break;
			case CH_BOSS1:
			case CH_BOSS2:
			case CH_BOSS3:
				textcolor(DarkPurple);
				break;
			case CH_PLAYER:
				textcolor(BLUE);
				break;
			case CH_BULLET:
				textcolor(DarkYellow);
				break;
			case CH_HPUP:
				textcolor(DarkGreen);
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
		if (m_player != nullptr)
		{
			if (i < m_player->GetHP())
			{
				cout << "▒";
			}
			else
			{
				cout << " ";
			}
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
	str = "";
	if (m_player != nullptr)
	{
		str = to_string(m_player->GetMoney());
	}
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
	str = "";
	if (m_player != nullptr)
	{
		str = to_string(m_player->GetAttack());
	}
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

	int idx = m_stageManager->GetCurrentStageIndex();

	if (idx == 3)
	{
		cout << "BOSS HP : ";
		if (!m_gameobjects[MONSTER].empty())
		{
			shared_ptr<BossMonster> boss = dynamic_pointer_cast<BossMonster> (m_gameobjects[MONSTER][0]);

			for (int i = 0; i < 30; i++)
			{
				if (i < boss->GetHP())
				{
					cout << "▒";
				}
				else
				{
					cout << " ";
				}
			}
		}
		else
		{
			for (int i = 0; i < 30; i++)
			{
				cout << " ";
			}
		}
	}
	else
	{
		cout << "KILL COUNT : ";
		str = "";
		if (m_player != nullptr)
		{
			str = to_string(m_player->GetKillCnt());
		}
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
		cout << " / " << (m_stageManager->GetCurrentStageIndex() + 1) * 10;
	}

	


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
	str = "";
	if (m_player != nullptr)
	{
		str = to_string(m_player->GetSkillCnt()[0]);
	}
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
	str = "";
	if (m_player != nullptr)
	{
		str = to_string(m_player->GetSkillCnt()[1]);
	}
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
	str = "";
	if (m_player != nullptr)
	{
		str = to_string(m_player->GetSkillCnt()[2]);
	}
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

void GameScene::DrawUI()
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

void GameScene::Input()
{
	m_player->Input();
}

void GameScene::ChangeScene()
{
	if (m_stageManager->GetCurrentStageIndex() == m_stageManager->GetStagesSize())
		SceneManager::Instance().ChangeScene("Ending");
	if (!m_player->GetAlive())
		SceneManager::Instance().ChangeScene("Title");

}




