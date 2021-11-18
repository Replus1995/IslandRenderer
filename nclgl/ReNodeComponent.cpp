#include "ReNodeComponent.h"
#include "ReSceneNode.h"

ReNodeComponent::ReNodeComponent()
	: mParent(NULL)
{
}

Matrix4 ReNodeComponent::GetTransform() const
{
	return mParent ? mParent->GetTransform() : Matrix4();
}

Matrix4 ReNodeComponent::GetWorldTransform() const
{
	return mParent ? mParent->GetWorldTransform() : Matrix4();
}
