#pragma once
#include "../../nclgl/RePrimitiveComponent.h"

class WaterComponent : public RePrimitiveComponent
{
public:
	WaterComponent(const RePrimitivePtr& InQuad)
		: RePrimitiveComponent(InQuad)
		, mCycle(0.0f)
		, mRotate(0.0f)
	{};
	virtual ~WaterComponent() {};

	virtual void Update(float msec) 
	{
		mRotate += msec * 0.5f;
		mCycle += msec * 0.1f;
	};

	virtual void Draw(bool bUseMaterial = true)
	{
		Matrix4 TexMatrix = Matrix4::Translation(Vector3(mCycle, 0.0f, mCycle)) *
							Matrix4::Scale(Vector3(10, 10, 10)) *
							Matrix4::Rotation(mRotate, Vector3(0, 0, 1));
		if (mPrimitive)
		{
			mPrimitive->GetMaterial()->SetShaderMatrix4("textureMatrix", TexMatrix);
		}
		RePrimitiveComponent::Draw(bUseMaterial);
		
	};

protected:
	float mCycle;
	float mRotate;
};
