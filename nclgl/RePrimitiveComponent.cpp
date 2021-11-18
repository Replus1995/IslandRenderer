#include "RePrimitiveComponent.h"

RePrimitiveComponent::RePrimitiveComponent(RePrimitivePtr InPrimitive)
	: mPrimitive(InPrimitive)
{
}

RePrimitiveComponent::~RePrimitiveComponent()
{
}

bool RePrimitiveComponent::IsTransparent() const
{
	return mPrimitive ? mPrimitive->IsTransparent() : false;
}

void RePrimitiveComponent::Draw(bool bUseMaterial)
{
	if (!mPrimitive) return;
	if (bUseMaterial)
		mPrimitive->UpdateMaterialParams();
	mPrimitive->DrawMesh();
}


Vector3 RePrimitiveComponent::GetPosition() const
{
	return  GetWorldTransform().GetPositionVector();
}

float RePrimitiveComponent::GetBoundingRadius() const
{
	float MeshRadius = mPrimitive ? mPrimitive->GetBoundingRadius() : 0.0f;
	Vector3 VecRadius = GetWorldTransform().GetScalingVector() * MeshRadius;
	float MaxRadius = std::max(std::max(VecRadius.x, VecRadius.y), VecRadius.z);
	return MaxRadius;
}

Shader* RePrimitiveComponent::GetShader() const
{
	return mPrimitive ? mPrimitive->GetMaterial()->GetShader() : nullptr;
}
