#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Mesh.h"
#include <vector>
#include <functional>

class ReNodeComponent;

class ReSceneNode
{
public:
	ReSceneNode();
	virtual ~ReSceneNode(void);

	void AddChild(std::shared_ptr<ReSceneNode> NewChild);
	std::shared_ptr<ReSceneNode> GetChild(unsigned int Index);

	void RemoveChild(unsigned int Index);
	void RemoveChild(ReSceneNode* InChild);
	void RemoveChild(std::shared_ptr<ReSceneNode> InChild);
	void RemoveAllChildren();

	void RemoveFromParent();

	void AddComponent(std::shared_ptr<ReNodeComponent> InComponent);
	void RemoveComponent(std::shared_ptr<ReNodeComponent> InComponent);
	void GetAllComponents(std::vector<std::shared_ptr<ReNodeComponent>>& OutComponents,
							std::function<bool(std::shared_ptr<ReNodeComponent>&)> CheckFunc);
	
	void SetTransform(const Matrix4& InTransform) { mLocalTrans = InTransform; }
	const Matrix4& GetTransform() const { return mLocalTrans; }
	Matrix4 GetWorldTransform() const { return mWorldTrans; }

	virtual void Update(float msec);

	std::vector<std::shared_ptr<ReSceneNode>>::const_iterator GetChildBegin()
	{
		return mChildren.begin();
	}
	std::vector<std::shared_ptr<ReSceneNode>>::const_iterator GetChildEnd()
	{
		return mChildren.end();
	}
	 
protected:
	ReSceneNode* mParent;
	std::vector<std::shared_ptr<ReSceneNode>> mChildren;
	std::vector<std::shared_ptr<ReNodeComponent>> mComponents;

	Matrix4 mWorldTrans;
	Matrix4 mLocalTrans;
};

typedef std::shared_ptr<ReSceneNode> ReSceneNodePtr;

