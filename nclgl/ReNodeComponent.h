#pragma once
#include <memory>
#include "Matrix4.h"

class ReNodeComponent
{
public:
	ReNodeComponent();
	virtual	~ReNodeComponent() {};

	virtual bool IsPrimitive() const { return false; };
	virtual void Update(float msec) {};
	
	Matrix4 GetTransform() const;
	Matrix4 GetWorldTransform() const;

protected:
	friend class ReSceneNode;
	ReSceneNode* mParent;
	
};

typedef std::shared_ptr<ReNodeComponent> ReNodeComponentPtr;