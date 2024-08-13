#pragma once
#include "Library.h"
#include "Monster.h"

// Node base class
class BehaviorTreeNode
{
protected:

public:
    BehaviorTreeNode() = default;
    virtual ~BehaviorTreeNode() = default;

    virtual NodeState Tick(shared_ptr<Monster>& owner) = 0;
};

// Composite Node
class CompositeNode : public BehaviorTreeNode
{
public:
    CompositeNode() = default;

    void AddChild(shared_ptr<BehaviorTreeNode> child);
   
protected:
    std::vector<shared_ptr<BehaviorTreeNode>> children;
};

// Sequence Node
class SequenceNode : public CompositeNode
{
public:
    using CompositeNode::CompositeNode;

    NodeState Tick(shared_ptr<Monster>& owner) override;
};

// Selector Node
class SelectorNode : public CompositeNode
{
public:
    using CompositeNode::CompositeNode;

    NodeState Tick(shared_ptr<Monster>& owner) override;
};

