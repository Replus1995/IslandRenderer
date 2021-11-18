#pragma once
#include "ReNodeComponent.h"
#include "ReFrustumObject.h"
#include "RePrimitive.h"


class RePointLightComponent : public ReNodeComponent, public ReFrustumObject
{
public:
	RePointLightComponent(RePrimitivePtr InPrim, const Vector4& InColour, const float InRadius);
	virtual ~RePointLightComponent();

	// Component Api//
	virtual void Update(float msec) {};
	// Component Api//

	// PointLight Api//
	virtual void Draw();
	// Primitive Api//

	// Frustum Api//
	virtual Vector3 GetPosition() const { return GetWorldTransform().GetPositionVector(); };
	virtual float GetBoundingRadius() const { return mLightRadius; };
	// Frustum Api//

	ReMaterialPtr GetMaterial() const;
	Shader* GetShader() const;

protected:
	RePrimitivePtr mLightPrim;
	Vector4 mLightColour;
	float mLightRadius;
};

typedef std::shared_ptr<RePointLightComponent> RePointLightComponentPtr;