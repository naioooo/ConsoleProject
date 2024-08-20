#pragma once
#include "Node.h"

class Boss_IsTimeToAttackCondition : public BehaviorTreeNode
{
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};

class Boss_IsAttackingNowCondition : public BehaviorTreeNode
{
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};

class Boss_AttackActionNode : public BehaviorTreeNode
{
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};

class Boss_WanderActionNode : public BehaviorTreeNode
{
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};