#pragma once
#include "BossBehaviorTree.h"
#include "GameScene.h"

NodeState Boss_IsPlayerInAttackRangeCondition::Tick(shared_ptr<Monster>& owner)
{
    vector<vector<shared_ptr<Object>>> gameobjects = GameScene::m_gameobjects;
    bool inRange = false;
    
    if (owner->isAttacked(gameobjects[PLAYER][0]->GetPoint()))
    {
        inRange = true;
    }

    return inRange ? NodeState::Success : NodeState::Failure;
}

NodeState Boss_IsPlayerDetectedCondition::Tick(shared_ptr<Monster>& owner)
{
    vector<vector<shared_ptr<Object>>> gameobjects = GameScene::m_gameobjects;
    bool playerDetected = false;
    
    if (owner->isDetected(gameobjects[PLAYER][0]->GetPoint()))
    {
        playerDetected = true;
    }

    return playerDetected ? NodeState::Success : NodeState::Failure;
}

NodeState Boss_AttackActionNode::Tick(shared_ptr<Monster>& owner)
{
    // 플레이어를 공격하는 로직을 구현합니다.
    shared_ptr<BossMonster> boss = dynamic_pointer_cast<BossMonster>(owner);
    
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> att(0, 2);

    switch (att(gen))
    {
    case 1:
        boss->ExplosiveFireBall(5, 5);
        break;
    case 2:
        boss->MeteorFireBall();
    default:
        break;
    }

    owner->SetState(ATTACK);
    return NodeState::Success; // 공격 완료
}

NodeState Boss_ChaseActionNode::Tick(shared_ptr<Monster>& owner)
{ 
    // 플레이어를 추적하는 로직을 구현합니다.
    vector<vector<shared_ptr<Object>>> gameobjects = GameScene::m_gameobjects;

    owner->AStar(gameobjects[PLAYER][0]->GetPoint());
    owner->Move(owner->GetPath()[0]);

    owner->SetState(CHASE);
    return NodeState::Running; // 추적 중이므로 Running 상태를 반환
}

NodeState Boss_WanderActionNode::Tick(shared_ptr<Monster>& owner)
{ 
    // 적이 배회하는 로직을 구현합니다. 
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dir(0, 4);

    owner->Move(dir(gen));

    owner->SetState(WANDER);
    return NodeState::Running; // 배회 중이므로 Running 상태를 반환
}

NodeState Boss_IsPlayerNotDetectedCondition::Tick(shared_ptr<Monster>& owner)
{
    // 플레이어가 탐지되지 않았는지 확인하는 로직을 구현합니다.
    bool playerNotDetected = true; 
    return playerNotDetected ? NodeState::Success : NodeState::Failure;
}
