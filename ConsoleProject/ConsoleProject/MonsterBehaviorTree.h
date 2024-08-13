#pragma once
#include "Node.h"

class IsPlayerDetectedCondition : public BehaviorTreeNode {
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};

class IsPlayerInAttackRangeCondition : public BehaviorTreeNode {
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};

class IsPlayerNotDetectedCondition : public BehaviorTreeNode {
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};

class ChaseActionNode : public BehaviorTreeNode {
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};

class AttackActionNode : public BehaviorTreeNode {
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};

class WanderActionNode : public BehaviorTreeNode {
public:
    NodeState Tick(shared_ptr<Monster>& owner) override;
};



