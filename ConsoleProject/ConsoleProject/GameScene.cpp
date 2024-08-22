#pragma once
#include "GameScene.h"

vector<vector<shared_ptr<Object>>> GameScene::m_gameObjects{};

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

	m_gameObjects.resize(4);
	m_gameObjects[PLAYER].push_back(make_shared <Player>(Point(MAX_WIDTH / 2, MAX_HEIGHT / 2), 30, 120, 50, 50, "호날두"));
	m_player = dynamic_pointer_cast<Player>(m_gameObjects[PLAYER][0]);

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

	for (auto& object : m_gameObjects)
	{
		object.clear();
		object.shrink_to_fit();
	}
	m_gameObjects.clear();
	m_gameObjects.shrink_to_fit();

	m_stageManager = nullptr;
}

void GameScene::Update(float elapsedTime)
{
	Input(elapsedTime);
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

	for (auto& objects : m_gameObjects)
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
	int idx = m_stageManager->GetCurrentStageIndex();

	GoToXY(x, y);
	string str;

	for (const auto& str : m_buffer)
	{
		for (const auto& ch : str)
		{
			switch (ch)
			{
			case CH_OBSTACLE:
				//TextColor(WHITE);
				TextColor(WHITE | WHITE<<4);
				break;
			case CH_FIREBALL:
				TextColor(RED);
				break;
			case CH_MONSTER1:
			case CH_MONSTER2:
			case CH_MONSTER3:
				TextColor(DARKRED);
				break;
			case CH_BOSS1:
			case CH_BOSS2:
			case CH_BOSS3:
				TextColor(DARKPURPLE);
				break;
			case CH_PLAYER:
				TextColor(BLUE);
				break;
			case CH_BULLET:
				TextColor(DARKYELLOW);
				break;
			case CH_HPUP:
				TextColor(DARKGREEN);
				break;
			case CH_MONEY:
				TextColor(YELLOW);
				break;
			case CH_SPEEDUP:
				TextColor(DARKSKYBLUE);
				break;
			case CH_ATTACKUP:
				TextColor(PURPLE);
				break;
			}

			cout << ch;
			TextColor(BLACK);
		}
		GoToXY(x, ++y);
	}		

	// 게임 정보 출력
	x = 90;
	y = 6;
	GoToXY(x, y);

	TextColor(WHITE);

	if (idx == m_stageManager->GetStagesSize() - 1)
	{
		cout << "BOSS STAGE" ;
	}
	else
	{
		cout << "STAGE " << idx + 1;
	}

	x = 75;
	y += 2;
	GoToXY(x, y);

	TextColor(RED);
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
	GoToXY(x, y);
	TextColor(YELLOW);
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
	GoToXY(x, y);
	TextColor(DARKRED);
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
	GoToXY(x, y);
	TextColor(DARKSKYBLUE);
	cout << "SPEED : ";
	str = "";
	if (m_player != nullptr)
	{
		str = to_string(120 - m_player->GetSpeed());
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
	GoToXY(x, y);
	TextColor(RED);

	if (idx == m_stageManager->GetStagesSize() - 1)
	{
		cout << "BOSS HP : ";
		if (!m_gameObjects[MONSTER].empty())
		{
			shared_ptr<BossMonster> boss = dynamic_pointer_cast<BossMonster> (m_gameObjects[MONSTER][0]);

			for (int i = 0; i < 3000; i += 100)
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

	y++;
	GoToXY(x, y);
	TextColor(RED);
	if (m_player->GetInvincibility())
	{
		cout << "무적";
	}
	else
	{
		cout << "     ";
	}

	/////////
	x = 75;
	y += 4;
	TextColor(WHITE);
	GoToXY(x, y);
	cout << "buy   : ";

	x += 8;
	GoToXY(x, y);
	cout << " Q";

	x += 9;
	GoToXY(x, y);
	cout << " W";

	x += 9;
	GoToXY(x, y);
	cout << " E";

	//

	x = 75;
	y++;
	GoToXY(x, y);
	cout << "use   : ";

	x += 8;
	GoToXY(x, y);
	cout << " A";

	x += 9;
	GoToXY(x, y);
	cout << " S";

	x += 9;
	GoToXY(x, y);
	cout << " D";

	//

	x = 75;
	y += 2;
	TextColor(WHITE);
	GoToXY(x, y);
	cout << "skill : ";

	x += 8;
	GoToXY(x, y);
	cout << " 회복";

	x += 9;
	GoToXY(x, y);
	cout << " 범위기";

	x += 9;
	GoToXY(x, y);
	cout << " 레이저";

	//

	x = 75;
	y++;
	GoToXY(x, y);
	cout << "cost  : ";

	x += 8;
	GoToXY(x, y);
	cout << " 500 ";

	x += 9;
	GoToXY(x, y);
	cout << " 1000";

	x += 9;
	GoToXY(x, y);
	cout << " 1000";

	/////////
	x = 75;
	y++;
	GoToXY(x, y);
	cout << "count : ";

	x += 9;
	GoToXY(x, y);
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
	GoToXY(x, y);
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

	x += 9;
	GoToXY(x, y);
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

	int x = 55;
	int y = 2;
	GoToXY(x, y);

	cout << "SHOOTING GAME" << endl;

	x = 4;
	y = 4;
	int width = MAX_WIDTH;
	int height = MAX_HEIGHT;

	TextColor(WHITE);

	GoToXY(x, y);
	cout << s1;
	for (int i = 0; i < width; i++)
	{
		cout << s5;
	}
	cout << s2;

	for (int i = 1; i <= height; i++)
	{
		GoToXY(x, y + i);
		cout << s6;
		for (int j = 0; j < width; j++)
		{
			cout << " ";
		}
		cout << s6 ;
	}

	GoToXY(x, y + height + 1);
	cout << s3;
	for (int i = 0; i < width; i++)
	{
		cout << s5;
	}
	cout << s4;

	///////////////////////////////////////////////////////////////////////
	
	x = 70; y = 4;
	width = 45; height = 20;

	GoToXY(x, y);
	cout << s1;
	for (int i = 0; i < width; i++)
	{
		cout << s5;
	}
	cout << s2;

	for (int i = 1; i <= height; i++)
	{
		GoToXY(x, y + i);
		cout << s6;
		for (int j = 0; j < width; j++)
		{
			cout << " ";
		}
		cout << s6;
	}

	GoToXY(x, y + height + 1);
	cout << s3;
	for (int i = 0; i < width; i++)
	{
		cout << s5;
	}
	cout << s4;
	
}

void GameScene::Input(float elapsedTime)
{
	m_player->Input(elapsedTime);
}

void GameScene::ChangeScene()
{
	if (m_stageManager->GetCurrentStageIndex() == m_stageManager->GetStagesSize())
		SceneManager::Instance().ChangeScene("Ending");
	if (!m_player->GetAlive())
		SceneManager::Instance().ChangeScene("Title");

}




