#pragma once
#include "MonsterBehaviorTree.h"
#include "GameScene.h"

NodeState IsPlayerDetectedCondition::Tick(shared_ptr<Monster>& owner)
{
    vector<vector<shared_ptr<Object>>> gameObjects = GameScene::m_gameObjects;
    bool playerDetected = false; 

    if (gameObjects[PLAYER][0]->GetPoint() != owner->GetChasePoint())
    {
        if (owner->isDetected(gameObjects[PLAYER][0]->GetPoint()))
        {
            playerDetected = true;
        }
    }    

    return playerDetected ? NodeState::Success : NodeState::Failure;
}

NodeState IsPlayerInAttackRangeCondition::Tick(shared_ptr<Monster>& owner)
{
    vector<vector<shared_ptr<Object>>> gameObjects = GameScene::m_gameObjects;
    bool inRange = false;

    if (gameObjects[PLAYER][0]->GetPoint() != owner->GetChasePoint())
    {
        if (owner->isAttacked(gameObjects[PLAYER][0]->GetPoint()))
        {
            inRange = true;
        }
    }

    return inRange ? NodeState::Success : NodeState::Failure;
}

NodeState IsPlayerNotDetectedCondition::Tick(shared_ptr<Monster>& owner)
{
    // 플레이어가 탐지되지 않았는지 확인하는 로직을 구현합니다.
    bool playerNotDetected = true; // 예시, 실제 로직으로 변경해야 합니다.
    return playerNotDetected ? NodeState::Success : NodeState::Failure;
}

NodeState ChaseActionNode::Tick(shared_ptr<Monster>& owner)
{
    // 플레이어를 추적하는 로직을 구현합니다.
    vector<vector<shared_ptr<Object>>> gameObjects = GameScene::m_gameObjects;

    owner->AStar(gameObjects[PLAYER][0]->GetPoint());
    owner->Move(owner->GetPath()[0]);

    owner->SetState(CHASE);
    return NodeState::Running; // 추적 중이므로 Running 상태를 반환
}

NodeState AttackActionNode::Tick(shared_ptr<Monster>& owner)
{
    // 플레이어를 공격하는 로직을 구현합니다.
    vector<vector<shared_ptr<Object>>> gameObjects = GameScene::m_gameObjects;
    shared_ptr<Player> player = dynamic_pointer_cast<Player>(gameObjects[PLAYER][0]);
    player->SetHP(player->GetHP() - owner->GetAttack());

    owner->SetState(ATTACK);
    return NodeState::Success; // 공격 완료
}

NodeState WanderActionNode::Tick(shared_ptr<Monster>& owner)
{
    // 적이 배회하는 로직을 구현합니다. 
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dir(1, 4);

    owner->Move(dir(gen));

    owner->SetState(WANDER);
    return NodeState::Running; // 배회 중이므로 Running 상태를 반환
}
