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

	vector<int> m_skillCnt;
	int m_reloadCnt;	
	int m_killCnt;

public:
	Player();
	Player(const Point point, const int HP, const int speed, const int attack, const int defense, const string& name);
	~Player();

	void InsertBuffer(vector<string>& buffer) override;
	void Update(float elapsedTime) override;

	unsigned int GetMoney();
	int GetKillCnt();
	vector<int> GetSkillCnt();

	void SetMoney(const unsigned int money);
	void SetKillCnt(const int killCnt);

	void Input();
	void Move() override;
	void Attack() override;
	bool CollisionCheck(Point point) override;
};

