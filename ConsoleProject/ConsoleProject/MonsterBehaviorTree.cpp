#pragma once
#include "MonsterBehaviorTree.h"
#include "GameScene.h"

NodeState IsPlayerDetectedCondition::Tick(shared_ptr<Monster>& owner)
{
    vector<vector<shared_ptr<Object>>> gameobjects = GameScene::m_gameobjects;
    bool playerDetected = false; 

    if (gameobjects[PLAYER][0]->getpoint() != owner->getchasePoint())
    {
        if (owner->isDetected(gameobjects[PLAYER][0]->getpoint()))
        {
            playerDetected = true;
        }
    }    

    return playerDetected ? NodeState::Success : NodeState::Failure;
}

NodeState IsPlayerInAttackRangeCondition::Tick(shared_ptr<Monster>& owner)
{
    vector<vector<shared_ptr<Object>>> gameobjects = GameScene::m_gameobjects;
    bool inRange = false;

    if (gameobjects[PLAYER][0]->getpoint() != owner->getchasePoint())
    {
        if (owner->isAttacked(gameobjects[PLAYER][0]->getpoint()))
        {
            inRange = true;
        }
    }

    return inRange ? NodeState::Success : NodeState::Failure;
}

NodeState IsPlayerNotDetectedCondition::Tick(shared_ptr<Monster>& owner)
{
    // �÷��̾ Ž������ �ʾҴ��� Ȯ���ϴ� ������ �����մϴ�.
    bool playerNotDetected = true; // ����, ���� �������� �����ؾ� �մϴ�.
    return playerNotDetected ? NodeState::Success : NodeState::Failure;
}

NodeState ChaseActionNode::Tick(shared_ptr<Monster>& owner)
{
    // �÷��̾ �����ϴ� ������ �����մϴ�.
    vector<vector<shared_ptr<Object>>> gameobjects = GameScene::m_gameobjects;

    owner->AStar(gameobjects[PLAYER][0]->getpoint());
    owner->move(owner->getpath()[0]);

    return NodeState::Running; // ���� ���̹Ƿ� Running ���¸� ��ȯ
}

NodeState AttackActionNode::Tick(shared_ptr<Monster>& owner)
{
    // �÷��̾ �����ϴ� ������ �����մϴ�.
    return NodeState::Success; // ���� �Ϸ�
}

NodeState WanderActionNode::Tick(shared_ptr<Monster>& owner)
{
    // ���� ��ȸ�ϴ� ������ �����մϴ�. 
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dir(0, 4);

    owner->move(dir(gen));

    return NodeState::Running; // ��ȸ ���̹Ƿ� Running ���¸� ��ȯ
}
