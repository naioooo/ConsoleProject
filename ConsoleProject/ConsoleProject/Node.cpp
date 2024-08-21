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
        if (status != NodeState::SUCCESS)
        {
            return status;
        }
    }
    return NodeState::SUCCESS;
}

NodeState SelectorNode::Tick(shared_ptr<Monster>& owner)
{
    for (auto& child : children)
    {
        NodeState status = child->Tick(owner);
        if (status != NodeState::FAILURE)
        {
            return status;
        }
    }
    return NodeState::FAILURE;
}

