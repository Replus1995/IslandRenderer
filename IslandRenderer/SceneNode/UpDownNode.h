#pragma once
#include "../../nclgl/ReSceneNode.h"

class UpDownNode : public ReSceneNode
{
public:
	UpDownNode() {};
	~UpDownNode() {};

	virtual void Update(float msec) 
	{
		mNodeTime += msec;
		Vector3 tTranslation = Vector3(0, (1.0f + sin(mNodeTime)) * 0.5, 0);
		mLocalTrans = Matrix4::Translation(tTranslation) * Matrix4::Rotation(mNodeTime * 30, Vector3(0, 1, 0));
		ReSceneNode::Update(msec);
	};

protected:
	float mNodeTime = 0.0f;
};