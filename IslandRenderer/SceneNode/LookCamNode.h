#pragma once
#include <memory>
#include "../../nclgl/ReSceneNode.h"
#include "../../nclgl/Camera.h"

class LookCamNode : public ReSceneNode
{
public:
	LookCamNode(const std::shared_ptr<Camera>& InCamera) 
		: mCamera(InCamera)
	{};
	~LookCamNode() {};

	virtual void Update(float msec)
	{
		Vector3 CurLocation = Vector3(0, 0, 0);
		if (mParent)
		{
			CurLocation = mParent->GetWorldTransform().GetPositionVector();
		}
		/*Matrix4 Rotation = Matrix4::BuildViewMatrix(CurLocation, mCamera->GetPosition());
		Rotation.SetPositionVector(Vector3(0, 0, 0));*/
		Matrix4 Rotation = Matrix4::ModelLookAt(CurLocation, mCamera->GetPosition());
		mLocalTrans = Rotation * Matrix4::Rotation(180,Vector3(1,0,0));
		ReSceneNode::Update(msec);
	};

protected:
	std::shared_ptr<Camera> mCamera;
};