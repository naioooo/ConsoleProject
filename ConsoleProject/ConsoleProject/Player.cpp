#pragma once
#include "Player.h"

Player::Player()
{
}

Player::Player(const Point point, const int HP, const int speed, const int attack, const int defense, const string& name)
	: Character(point, HP, speed, attack, defense), m_name(name)
{
}

Player::~Player()
{
}

void Player::move()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { //왼쪽
		if (m_point.x > 0)
		{
			m_point.x--;
		}
		
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { //오른쪽		
		if (m_point.x < MAX_WIDTH - 2)
		{
			m_point.x++;
		}
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) { //위
		if (m_point.y > 0)
		{
			m_point.y--;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //아래
		if (m_point.y < MAX_HEIGHT - 2)
		{
			m_point.y++;
		}
	}

	/*
	switch (ch)
	{
	case 'w':
		if (m_point.y > 0)
		{
			m_point.y--;
		}
		break;
	case 's':
		if (m_point.y < 99)
		{
			m_point.y++;
		}
		break;
	case 'a':
		if (m_point.x > 0)
		{
			m_point.x--;
		}
		break;
	case 'd':
		if (m_point.x < 99)
		{
			m_point.x++;
		}
		break;

	default:
		break;
	}
	*/
}

void Player::attack()
{
}

void Player::insertbuffer(vector<string>& buffer)
{
	buffer[m_point.y][m_point.x] = '@';
}
