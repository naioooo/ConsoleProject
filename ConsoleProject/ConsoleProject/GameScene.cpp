#pragma once
#include "GameScene.h"

vector<vector<shared_ptr<Object>>> GameScene::m_gameobjects{};

GameScene::GameScene()
{
	m_gameobjects.resize(4);

	string str;
	str.resize(MAX_WIDTH, ' ');

	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		m_buffer.push_back(str);
	}

	m_generate_tick = 0;
	generate_map();

	m_gameobjects[PLAYER].push_back(make_shared <Player>(Point(10, 10), 100, 1, 50, 50, "호날두"));
	m_player = dynamic_pointer_cast<Player>(m_gameobjects[PLAYER][0]);

	generate_monster();

	draw_UI();
}

GameScene::GameScene(Player* &player)
{
	string str;
	str.resize(MAX_WIDTH, ' ');

	for (int i = 0; i < MAX_HEIGHT; i++)
	{
		m_buffer.push_back(str);
	}
	m_generate_tick = 0;
}

GameScene::~GameScene()
{
}

void GameScene::loop(float elapsedTime)
{
	input();
	update(elapsedTime);
	draw();
}

void GameScene::draw()
{
	int x = 5;
	int y = 5;
	gotoxy(x, y);

	for (const auto& str : m_buffer)
	{
		for (const auto& ch : str)
		{
			switch (ch)
			{
			case '#':
				textcolor(WHITE);
				break;
			case '!':
				textcolor(RED);
				break;
			case '@':
				textcolor(BLUE);
				break;
			case '*':
				textcolor(YELLOW);
				break;
			}

			cout << ch;
			textcolor(BLACK);
		}
		gotoxy(x, ++y);
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

	int x = 4;
	int y = 4;
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
	//오브젝트를 생성한다
	//generate_object();
		
	for (auto& objects : m_gameobjects)
	{
		for (auto& object : objects)
		{
			object->update(elapsedTime);
		}
	}
	
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

	//죽은 개체는 벡터에서 삭제한다
	for (auto& objects : m_gameobjects)
	{
		auto newEnd = std::remove_if(objects.begin(), objects.end(), [](shared_ptr<Object>& obj)
			{
				return !obj->getalive();
			});

		objects.erase(newEnd, objects.end());
	}

}

void GameScene::generate_object()
{
	if (m_generate_tick > 10)
	{
		generate_monster();
		m_generate_tick = 0;
	}

	m_generate_tick++;
}

void GameScene::generate_map()
{
	mt19937 gen(m_rd());

	uniform_int_distribution<int> width(0, MAX_WIDTH - 1);
	uniform_int_distribution<int> height(0, MAX_HEIGHT - 1);

	int cnt = 0;
	int i = 5;

	while (true)
	{
		if (cnt > 50)
			break;

		Point new_pos = Point(width(gen), height(gen));
		

		if (collision_object(new_pos))
		{
			m_gameobjects[OBSTACLE].push_back(make_shared<Object>(new_pos));
			cnt++;
		}
	}
}

void GameScene::generate_monster()
{
	mt19937 gen(m_rd());
		
	uniform_int_distribution<int> width(0, MAX_WIDTH - 1);
	uniform_int_distribution<int> height(0, MAX_HEIGHT - 1);
	
	int cnt = 0;

	while (true)
	{
		if (cnt >= 50)
			break;

		Point new_pos = Point(width(gen), height(gen));

		if (collision_object(new_pos))
		{
			m_gameobjects[MONSTER].push_back(make_shared<Monster>(new_pos, 100, 10, 50, 50));
			cnt++;
		}
	}
	
}

void GameScene::generate_item()
{


}

bool GameScene::collision_object(Point point)
{
	for (int i = 0; i < 4; i++)
	{
		for (auto& object : m_gameobjects[i])
		{
			if (object->getpoint() == point)
			{
				return false;
			}
		}
	}

	return true;
}



