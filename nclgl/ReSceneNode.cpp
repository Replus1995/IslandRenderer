#include "ReSceneNode.h"
#include "ReNodeComponent.h"

ReSceneNode::ReSceneNode()
	: mParent(NULL)
{
}

ReSceneNode::~ReSceneNode(void)
{
}

void ReSceneNode::AddChild(std::shared_ptr<ReSceneNode> NewChild)
{
	NewChild->RemoveFromParent();
	NewChild->mParent = this;
	mChildren.push_back(NewChild);
}

std::shared_ptr<ReSceneNode> ReSceneNode::GetChild(unsigned int Index)
{
	if (Index >= mChildren.size()) return nullptr;
	return mChildren[Index];
}

void ReSceneNode::RemoveChild(unsigned int Index)
{
	if (Index >= mChildren.size()) return;
	mChildren.erase(mChildren.begin() + Index);
}

void ReSceneNode::RemoveChild(ReSceneNode* InChild)
{
	for (auto& Child = mChildren.begin(); Child != mChildren.end(); ++Child)
	{
		if ((*Child).get() == InChild)
		{
			mChildren.erase(Child);
			return;
		}
	}
}

void ReSceneNode::RemoveChild(std::shared_ptr<ReSceneNode> InChild)
{
	for (auto& Child = mChildren.begin(); Child != mChildren.end(); ++Child)
	{
		if ((*Child) == InChild)
		{
			mChildren.erase(Child);
			return;
		}
	}
}

void ReSceneNode::RemoveAllChildren()
{
	mChildren.clear();
	mChildren.shrink_to_fit();
}

void ReSceneNode::RemoveFromParent()
{
	if (mParent)
	{
		mParent->RemoveChild(this);
	}
}

void ReSceneNode::AddComponent(std::shared_ptr<ReNodeComponent> InComponent)
{
	if (InComponent->mParent)
	{
		InComponent->mParent->RemoveComponent(InComponent);
	}
	InComponent->mParent = this;
	mComponents.push_back(InComponent);
}

void ReSceneNode::RemoveComponent(std::shared_ptr<ReNodeComponent> InComponent)
{
	for (auto& Component = mComponents.begin(); Component != mComponents.end(); ++Component)
	{
		if ((*Component) == InComponent)
		{
			mComponents.erase(Component);
			return;
		}
	}
}

void ReSceneNode::GetAllComponents(std::vector<std::shared_ptr<ReNodeComponent>>& OutComponents, std::function<bool(std::shared_ptr<ReNodeComponent>&)> CheckFunc)
{
	for (ReNodeComponentPtr& Component : mComponents)
	{
		if (CheckFunc(Component))
		{
			OutComponents.push_back(Component);
		}
	}
}

void ReSceneNode::Update(float msec)
{
	if (mParent)
	{
		mWorldTrans = mParent->mWorldTrans * mLocalTrans;
	}
	else
	{
		mWorldTrans = mLocalTrans;
	}

	for (auto& Component = mComponents.begin(); Component != mComponents.end(); ++Component)
	{
		(*Component)->Update(msec);
	}

	for (auto& Child = mChildren.begin(); Child != mChildren.end(); ++Child)
	{
		(*Child)->Update(msec);
	}
}
