#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include "RePrimitive.h"

class ReDLight
{
public:
	ReDLight(const RePrimitivePtr& InDLightPrim)
		: mDLightPrim(InDLightPrim)
		, mDirection(Vector3(0, -1, 0))
		, mColour(Vector4(1, 1, 1, 1))
		, mStrength(0.8f)
		, mDistance(10000.0f)
	{};
	~ReDLight() {};

	void UpdateDLightParam(const Vector3& InDrection, const Vector4& InColour, float InStrength, float InDistance)
	{
		mDirection = InDrection;
		mColour = InColour;
		mStrength = InStrength;
		mDistance = InDistance;
		return;
	};

	Vector3 GetDirVector() const { return mDirection; };
	float GetDistance() const { return mDistance; };
	Vector3 GetPosition() const { return mDirection * mDistance * -1.0f; };

	Shader* GetShader()
	{
		return mDLightPrim ? mDLightPrim->GetMaterial()->GetShader() : nullptr;
	};

	void Draw()
	{
		if (!mDLightPrim) return;

		glUniform3fv(glGetUniformLocation(GetShader()->GetProgram(), "lightDir"), 1, (float*)&mDirection);
		glUniform4fv(glGetUniformLocation(GetShader()->GetProgram(), "lightColour"), 1, (float*)&mColour);
		glUniform1f(glGetUniformLocation(GetShader()->GetProgram(), "lightStrength"), mStrength);

		mDLightPrim->DrawMesh();
	};

protected:
	Vector3 mDirection;
	Vector4 mColour;
	float mStrength;
	float mDistance;

	RePrimitivePtr mDLightPrim;
};