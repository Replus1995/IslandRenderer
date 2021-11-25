#pragma once
#include <string>
#include "ReFrustumObject.h"
#include "ReNodeComponent.h"
#include "RePrimitive.h"

class RePrimitiveComponent : public ReNodeComponent, public ReFrustumObject
{
public:
	RePrimitiveComponent(const RePrimitivePtr& InPrimitive);
	virtual ~RePrimitiveComponent();

	// Component Api//
	virtual void Update(float msec) {};
	// Component Api//

	// Primitive Api//
	virtual bool IsTransparent() const;
	virtual bool IsInstanced() const;
	virtual void Draw(bool bUseMaterial = true);
	// Primitive Api//

	virtual bool CastShadow() const { return mCastShadow; };
	virtual void SetCostShadow(bool InCastShadow) { mCastShadow = InCastShadow; };
	
	// Frustum Api//
	virtual Vector3 GetPosition() const;
	virtual float GetBoundingRadius() const;
	// Frustum Api//
	
	RePrimitivePtr GetPrimitive() const { return mPrimitive; }
	Shader* GetShader() const;

protected:
	RePrimitivePtr mPrimitive;
	bool mCastShadow = true;
};

typedef std::shared_ptr<RePrimitiveComponent> RePrimitiveComponentPtr;