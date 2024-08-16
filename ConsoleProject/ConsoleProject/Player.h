#pragma once
#include "Character.h"
#include "Bullet.h"

class Player :
	public Character
{
private:
	string m_name;
	vector<shared_ptr<Bullet>> m_bullets;
	unsigned int m_money;

	vector<int> m_skill_cnt;
	int m_reload_cnt;	
	int m_kill_cnt;

public:
	Player();
	Player(const Point point, const int HP, const int speed, const int attack, const int defense, const string& name);
	~Player();

	void insertbuffer(vector<string>& buffer) override;
	void update(float elapsedTime) override;

	unsigned int getmoney();
	int getkill_cnt();
	vector<int> getskill_cnt();

	void setmoney(const unsigned int money);
	void setkill_cnt(const int kill_cnt);

	void input();
	void move() override;
	void attack() override;
	bool collision_check(Point point) override;
};

