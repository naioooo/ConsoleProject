#pragma once
#include "MonsterBehaviorTree.h"
#include "GameScene.h"

NodeState IsPlayerDetectedCondition::Tick(shared_ptr<Monster>& owner)
{
    vector<vector<shared_ptr<Object>>> gameObjects = GameScene::m_gameObjects;
    bool playerDetected = false; 
    
    if (owner->isDetected(gameObjects[PLAYER][0]->GetPoint()))
    {
        playerDetected = true;
    }

    return playerDetected ? NodeState::SUCCESS : NodeState::FAILURE;
}

NodeState IsPlayerInAttackRangeCondition::Tick(shared_ptr<Monster>& owner)
{
    vector<vector<shared_ptr<Object>>> gameObjects = GameScene::m_gameObjects;
    bool inRange = false;
    
    if (owner->isAttacked(gameObjects[PLAYER][0]->GetPoint()))
    {
        inRange = true;
    }

    return inRange ? NodeState::SUCCESS : NodeState::FAILURE;
}

NodeState IsPlayerNotDetectedCondition::Tick(shared_ptr<Monster>& owner)
{
    bool playerNotDetected = true;
    return playerNotDetected ? NodeState::SUCCESS : NodeState::FAILURE;
}

NodeState ChaseActionNode::Tick(shared_ptr<Monster>& owner)
{
    vector<vector<shared_ptr<Object>>> gameObjects = GameScene::m_gameObjects;

    owner->AStar(gameObjects[PLAYER][0]->GetPoint());
    owner->Move(owner->GetPath()[0]);

    owner->SetState(CHASE);
    return NodeState::RUNNING;
}

NodeState AttackActionNode::Tick(shared_ptr<Monster>& owner)
{
    vector<vector<shared_ptr<Object>>> gameObjects = GameScene::m_gameObjects;
    shared_ptr<Player> player = dynamic_pointer_cast<Player>(gameObjects[PLAYER][0]);
    if (!player->GetInvincibility())
    {
        player->SetHP(player->GetHP() - owner->GetAttack());
    }

    owner->SetState(ATTACK);
    return NodeState::SUCCESS; 
}

NodeState WanderActionNode::Tick(shared_ptr<Monster>& owner)
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dir(1, 4);

    owner->Move(dir(gen));

    owner->SetState(WANDER);
    return NodeState::RUNNING; 
}
