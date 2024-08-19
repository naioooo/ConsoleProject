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
    // �÷��̾ �����ϴ� ������ �����մϴ�.
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
    return NodeState::Success; // ���� �Ϸ�
}

NodeState Boss_ChaseActionNode::Tick(shared_ptr<Monster>& owner)
{ 
    // �÷��̾ �����ϴ� ������ �����մϴ�.
    vector<vector<shared_ptr<Object>>> gameobjects = GameScene::m_gameobjects;

    owner->AStar(gameobjects[PLAYER][0]->GetPoint());
    owner->Move(owner->GetPath()[0]);

    owner->SetState(CHASE);
    return NodeState::Running; // ���� ���̹Ƿ� Running ���¸� ��ȯ
}

NodeState Boss_WanderActionNode::Tick(shared_ptr<Monster>& owner)
{ 
    // ���� ��ȸ�ϴ� ������ �����մϴ�. 
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dir(0, 4);

    owner->Move(dir(gen));

    owner->SetState(WANDER);
    return NodeState::Running; // ��ȸ ���̹Ƿ� Running ���¸� ��ȯ
}

NodeState Boss_IsPlayerNotDetectedCondition::Tick(shared_ptr<Monster>& owner)
{
    // �÷��̾ Ž������ �ʾҴ��� Ȯ���ϴ� ������ �����մϴ�.
    bool playerNotDetected = true; 
    return playerNotDetected ? NodeState::Success : NodeState::Failure;
}
