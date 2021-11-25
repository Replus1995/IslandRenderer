#pragma once
#include "../../nclgl/RePrimitiveComponent.h"

class FireFlyComponent : public RePrimitiveComponent
{
public:
	FireFlyComponent(const RePrimitivePtr& InPrimitive, float InTimeOffset)
		: RePrimitiveComponent(InPrimitive)
		, mTime(InTimeOffset)
		, mEmissiveScale(0.0f)
	{};
	virtual ~FireFlyComponent() {};

	virtual void Update(float msec) 
	{
		mTime += msec;
		mEmissiveScale = (1.0f + sin(mTime)) * 0.4 + 0.2;
	};

	virtual void Draw(bool bUseMaterial = true)
	{
		mPrimitive->GetMaterial()->SetShaderFloat("emissiveScale", mEmissiveScale);
		RePrimitiveComponent::Draw(bUseMaterial);
		
	};

protected:
	float mTime;
	float mEmissiveScale;
};
