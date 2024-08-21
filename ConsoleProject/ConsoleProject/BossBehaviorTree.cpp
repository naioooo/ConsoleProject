#pragma once
#include "BossBehaviorTree.h"
#include "GameScene.h"

NodeState Boss_IsTimeToAttackCondition::Tick(shared_ptr<Monster>& owner)
{
    shared_ptr<BossMonster> boss = dynamic_pointer_cast<BossMonster>(owner);
    bool isCoolOn = false;

    if (boss->GetCoolTimeCnt() >= boss->GetCoolTime())
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> att(1, 6);

        vector<vector<shared_ptr<Object>>>& gameObjects{ GameScene::m_gameObjects };
        int choice = att(gen);
        int dir = 0;

        switch (choice)
        {
        case 1:            
            dir = DetermineDirection(owner->GetPoint(), gameObjects[PLAYER][0]->GetPoint());
            boss->SetDir(dir); 
            boss->SetSpeed(60);
            boss->SetAttackTime(10);
            break;
        case 2:
            boss->SetSpeed(60);
            boss->SetAttackTime(15);
            break;
        case 3:
            boss->SetAttackTime(3);
            break;
        case 4:
            boss->SetAttackTime(5);
            break;
        case 5:
            dir = DetermineDirection(owner->GetPoint(), gameObjects[PLAYER][0]->GetPoint());
            boss->SetDir(dir);
            boss->SetAttackTime(5);
            break;
        case 6:
            boss->SetAttackTime(10);
            break;
        }

        boss->SetIsAttack(choice);
        boss->SetCoolTimeCnt(0);
        isCoolOn = true;
    }
    else
    {
        boss->SetCoolTimeCnt(boss->GetCoolTimeCnt() + 1);
    }

    return isCoolOn ? NodeState::Success : NodeState::Failure;
}

NodeState Boss_IsAttackingNowCondition::Tick(shared_ptr<Monster>& owner)
{
    shared_ptr<BossMonster> boss = dynamic_pointer_cast<BossMonster>(owner);
    bool isAttack = false;

    if (boss->GetIsAttack() > 0)
    {    
        isAttack = true;
    }

    return isAttack ? NodeState::Success : NodeState::Failure;
}

NodeState Boss_AttackActionNode::Tick(shared_ptr<Monster>& owner)
{
    // 플레이어를 공격하는 로직을 구현합니다.
    shared_ptr<BossMonster> boss = dynamic_pointer_cast<BossMonster>(owner);
    
    switch (boss->GetIsAttack())
    {
    case 1:
        boss->ChargeAttack();
        break;
    case 2:
        boss->ChasePlayer();
        break;
    case 3:
        boss->ExplosiveFireBall(5, 5);
        break;
    case 4:
        boss->MeteorFireBall();
        break;
    case 5:
        boss->DirectionalBlast();
        break;
    case 6:
        boss->FireBallFromMapEdges();
        break;
    }

    boss->SetAttackTimeCnt(boss->GetAttackTimeCnt() + 1);

    if (boss->GetAttackTimeCnt() > boss->GetAttackTime())
    {
        boss->SetAttackTimeCnt(0);
        boss->SetIsAttack(0);
        boss->SetSpeed(180);
    }

    owner->SetState(ATTACK);
    return NodeState::Success; // 공격 완료
}

NodeState Boss_WanderActionNode::Tick(shared_ptr<Monster>& owner)
{
    shared_ptr<BossMonster> boss = dynamic_pointer_cast<BossMonster>(owner);
    // 적이 배회하는 로직을 구현합니다. 
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dir(1, 4);

    boss->Move(dir(gen));

    boss->SetState(WANDER);
    return NodeState::Running; // 배회 중이므로 Running 상태를 반환
}




