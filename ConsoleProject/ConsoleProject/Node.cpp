#pragma once
#include "Node.h"
#include "Monster.h"

void CompositeNode::AddChild(shared_ptr<BehaviorTreeNode> child)
{
    children.push_back(child);
}

NodeState SequenceNode::Tick(shared_ptr<Monster>& owner)
{
    for (auto& child : children)
    {
        NodeState status = child->Tick(owner);
        if (status != NodeState::Success)
        {
            return status;
        }
    }
    return NodeState::Success;
}

NodeState SelectorNode::Tick(shared_ptr<Monster>& owner)
{
    for (auto& child : children)
    {
        NodeState status = child->Tick(owner);
        if (status != NodeState::Failure)
        {
            return status;
        }
    }
    return NodeState::Failure;
}

