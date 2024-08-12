#pragma once
#include "Character.h"

class Player :
	public Character
{
private:
	string m_name;


public:
	Player();
	Player(const Point point, const int HP, const int speed, const int attack, const int defense, const string& name);
	~Player();

	void move(vector<vector<Object*>>& gameobjects);
	void attack();
	void insertbuffer(vector<string>& buffer);
};

