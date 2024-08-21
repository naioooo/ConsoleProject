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
    // �÷��̾ Ž������ �ʾҴ��� Ȯ���ϴ� ������ �����մϴ�.
    bool playerNotDetected = true; // ����, ���� �������� �����ؾ� �մϴ�.
    return playerNotDetected ? NodeState::Success : NodeState::Failure;
}

NodeState ChaseActionNode::Tick(shared_ptr<Monster>& owner)
{
    // �÷��̾ �����ϴ� ������ �����մϴ�.
    vector<vector<shared_ptr<Object>>> gameObjects = GameScene::m_gameObjects;

    owner->AStar(gameObjects[PLAYER][0]->GetPoint());
    owner->Move(owner->GetPath()[0]);

    owner->SetState(CHASE);
    return NodeState::Running; // ���� ���̹Ƿ� Running ���¸� ��ȯ
}

NodeState AttackActionNode::Tick(shared_ptr<Monster>& owner)
{
    // �÷��̾ �����ϴ� ������ �����մϴ�.
    vector<vector<shared_ptr<Object>>> gameObjects = GameScene::m_gameObjects;
    shared_ptr<Player> player = dynamic_pointer_cast<Player>(gameObjects[PLAYER][0]);
    player->SetHP(player->GetHP() - owner->GetAttack());

    owner->SetState(ATTACK);
    return NodeState::Success; // ���� �Ϸ�
}

NodeState WanderActionNode::Tick(shared_ptr<Monster>& owner)
{
    // ���� ��ȸ�ϴ� ������ �����մϴ�. 
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dir(1, 4);

    owner->Move(dir(gen));

    owner->SetState(WANDER);
    return NodeState::Running; // ��ȸ ���̹Ƿ� Running ���¸� ��ȯ
}
