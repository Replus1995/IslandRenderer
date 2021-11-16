#pragma once
#include <any>
#include "ReNodeComponent.h"
#include "RePrimitive.h"

class RePrimitiveComponent : public ReNodeComponent
{
public:
	RePrimitiveComponent(RePrimitivePtr InPrimitive);
	virtual ~RePrimitiveComponent();

	virtual bool IsPrimitive() const { return true; };
	virtual void Update(float msec) {};

	virtual void Draw();

	virtual bool IsTransparent() const;
	virtual float GetBoundingRadius() const;
	
	RePrimitivePtr GetPrimitive() const { return mPrimitive; }
	Shader* GetShader() const;

protected:
	RePrimitivePtr mPrimitive;
};

typedef std::shared_ptr<RePrimitiveComponent> RePrimitiveComponentPtr;