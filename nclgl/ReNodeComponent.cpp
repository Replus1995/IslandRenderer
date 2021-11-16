#include "ReNodeComponent.h"
#include "ReSceneNode.h"

ReNodeComponent::ReNodeComponent()
	: mParent(NULL)
{
}

Matrix4 ReNodeComponent::GetTransform() const
{
	if (mParent)
	{
		return mParent->GetTransform();
	}
	else
	{
		return Matrix4();
	}
}

Matrix4 ReNodeComponent::GetWorldTransform() const
{
	if (mParent)
	{
		return mParent->GetWorldTransform();
	}
	else
	{
		return Matrix4();
	}
}
