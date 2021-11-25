#pragma once
#include <memory>
#include <vector>
#include <map>
#include "FilterContainer.h"
#include "../nclgl/Vector3.h"
#include "../nclgl/Matrix4.h"

class Camera;
class ReFrustum;
class ReSceneNode;
class RePrimitive;

class PrimitiveFilter
{
public:
	PrimitiveFilter(const std::shared_ptr<Camera>& InCamera, const std::shared_ptr<ReFrustum>& InFrustum);
	~PrimitiveFilter() {}

	void FindPrimitives(const std::shared_ptr<ReSceneNode>& InNode);
	void SortPrimitives();
	void ClearPrimitives();

public:
	std::vector<PrimitiveContainer> mPrimitives_Transparent;
	std::vector<PrimitiveContainer> mPrimitives_Opaque;

	std::map<std::shared_ptr<RePrimitive>, std::vector<Matrix4>> mInstancedPrimitives;

protected:
	std::shared_ptr<Camera> mCamera;
	std::shared_ptr<ReFrustum> mFrustum;
};
