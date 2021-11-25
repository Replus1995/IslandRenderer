#pragma once
#include <memory>
#include <vector>
#include "../nclgl/Vector3.h"
#include "../nclgl/Matrix4.h"

class ReSceneNode;
class RePrimitiveComponent;

class ShadowFilter
{
public:
	ShadowFilter() {};
	~ShadowFilter() {}

	void FindPrimitives(const std::shared_ptr<ReSceneNode>& InNode);
	void ClearPrimitives();

public:
	std::vector<std::shared_ptr<RePrimitiveComponent>> mPrimitives_Opaque;

};
