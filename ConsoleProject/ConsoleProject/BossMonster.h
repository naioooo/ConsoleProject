#pragma once
#include "Monster.h"
#include "fireBall.h"


class BossMonster : public Monster
{
private:
	vector<shared_ptr<FireBall>> m_fireBall;
	int m_coolTime;
	int m_coolTimeCnt;
	int m_isAttack;

	int m_attackTime;
	int m_attackTimeCnt;

public:
	BossMonster();
	BossMonster(const Point point, const int HP, const int speed, const int attack, const int defense);
	~BossMonster();

	void InsertBuffer(vector<string>& buffer) override;
	void Update(float elapsedTime) override;
	void Move(const int dir) override;
	bool CollisionCheck(Point point) override;
	bool IsValidPoint(Point point) override;

	int GetCoolTime();
	int GetCoolTimeCnt();
	int GetIsAttack();
	int GetAttackTime();
	int GetAttackTimeCnt();

	void SetCoolTime(int coolTime);
	void SetCoolTimeCnt(int coolTimeCnt);
	void SetIsAttack(int isAttack);
	void SetAttackTime(int attackTime);
	void SetAttackTimeCnt(int attackTimeCnt);

	void ChargeAttack(); // ����
	void ChasePlayer(); // ���󰡱�
	void ExplosiveFireBall(int width, int height); // ���� ����
	void MeteorFireBall(); // ���׿�
	void DirectionalBlast(); // ��ǳ
	void fireBallfromMapEdges(); // �ʳ����� �߻�
};

