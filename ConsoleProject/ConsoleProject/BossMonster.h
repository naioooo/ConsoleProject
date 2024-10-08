#pragma once
#include "Monster.h"
#include "fireBall.h"


class BossMonster : public Monster
{
private:
	vector<shared_ptr<FireBall>> m_fireBall;

	int m_isAttack;

	int m_coolTime;
	int m_coolTimeCnt;

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
	bool IsFindPoint(shared_ptr<Node> current, Point goal) override;

	int GetCoolTime() const;
	int GetCoolTimeCnt() const;
	int GetIsAttack() const;
	int GetAttackTime() const;
	int GetAttackTimeCnt() const;

	void SetCoolTime(int coolTime);
	void SetCoolTimeCnt(int coolTimeCnt);
	void SetIsAttack(int isAttack);
	void SetAttackTime(int attackTime);
	void SetAttackTimeCnt(int attackTimeCnt);

	void ChargeAttack(); // 돌진
	void ChasePlayer(); // 따라가기
	void ExplosiveFireBall(int width, int height); // 전역 폭발
	void MeteorFireBall(); // 메테오
	void DirectionalBlast(); // 장풍
	void FireBallFromMapEdges(); // 맵끝에서 발사
};

