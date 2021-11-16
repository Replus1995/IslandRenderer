#include "RePrimitiveComponent.h"

RePrimitiveComponent::RePrimitiveComponent(RePrimitivePtr InPrimitive)
	: mPrimitive(InPrimitive)
{
}

RePrimitiveComponent::~RePrimitiveComponent()
{
}


void RePrimitiveComponent::Draw()
{
	if (!mPrimitive) return;

	mPrimitive->UpdateMaterialParams();
	mPrimitive->DrawMesh();
}

bool RePrimitiveComponent::IsTransparent() const
{
	return mPrimitive ? mPrimitive->IsTransparent() : false;
}

float RePrimitiveComponent::GetBoundingRadius() const
{
	return mPrimitive ? mPrimitive->GetBoundingRadius() : 0.0f;
}

Shader* RePrimitiveComponent::GetShader() const
{
	return mPrimitive ? mPrimitive->GetMaterial()->GetShader() : nullptr;
}
