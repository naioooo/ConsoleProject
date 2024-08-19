#pragma once
#include "Node.h"

class Boss_IsPlayerInAttackRangeCondition : public BehaviorTreeNode
{
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};

class Boss_IsPlayerDetectedCondition : public BehaviorTreeNode
{
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};

class Boss_IsPlayerNotDetectedCondition : public BehaviorTreeNode
{
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};

class Boss_AttackActionNode : public BehaviorTreeNode
{
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};

class Boss_ChaseActionNode : public BehaviorTreeNode
{
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};

class Boss_WanderActionNode : public BehaviorTreeNode
{
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};