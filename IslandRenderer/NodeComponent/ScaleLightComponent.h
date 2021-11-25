#pragma once
#include "../../nclgl/RePointLightComponent.h"

class ScaleLightComponent : public RePointLightComponent
{
public:
	ScaleLightComponent(const RePrimitivePtr& InPrim, const Vector4& InColour, const float InMaxRadius, float InTimeOffset)
		: RePointLightComponent(InPrim, InColour, 100.0f)
		, mMaxRadius(InMaxRadius)
		, mTime(InTimeOffset)
	{
	};
	virtual ~ScaleLightComponent() {};

	virtual void Update(float msec) 
	{
		mTime += msec;
		float tRadiusScale = (1.0f + sin(mTime)) * 0.45 + 0.1;
		mLightRadius = mMaxRadius * tRadiusScale;
	};

protected:
	float mTime;
	float mMaxRadius;
};