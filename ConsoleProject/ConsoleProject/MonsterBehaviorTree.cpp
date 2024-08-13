#pragma once
#include "MonsterBehaviorTree.h"
#include "GameScene.h"

NodeState IsPlayerDetectedCondition::Tick(shared_ptr<Monster>& owner)
{
    // �÷��̾ Ž���Ǿ����� ���θ� Ȯ���ϴ� ������ �����մϴ�.
    bool playerDetected = true; // ����, ���� �������� �����ؾ� �մϴ�.
    return playerDetected ? NodeState::Success : NodeState::Failure;
}

NodeState IsPlayerInAttackRangeCondition::Tick(shared_ptr<Monster>& owner)
{
    // �÷��̾ ���� ���� ���� �ִ��� Ȯ���ϴ� ������ �����մϴ�.
    bool inRange = false; // ����, ���� �������� �����ؾ� �մϴ�.
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

    //if (owner->getpath().empty())
    {
    }

    owner->AStar(gameobjects[PLAYER][0]->getpoint());
    owner->move(owner->getpath()[0]);

    gotoxy(100, 25);   

    std::cout << "Chasing player...\n";

    return NodeState::Running; // ���� ���̹Ƿ� Running ���¸� ��ȯ
}

NodeState AttackActionNode::Tick(shared_ptr<Monster>& owner)
{
    // �÷��̾ �����ϴ� ������ �����մϴ�.
    std::cout << "Attacking player...\n";
    return NodeState::Success; // ���� �Ϸ�
}

NodeState WanderActionNode::Tick(shared_ptr<Monster>& owner)
{
    // ���� ��ȸ�ϴ� ������ �����մϴ�. 
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dir(0, 4);

    owner->move(dir(gen));

    std::cout << "Wandering around...\n";
    return NodeState::Running; // ��ȸ ���̹Ƿ� Running ���¸� ��ȯ
}
