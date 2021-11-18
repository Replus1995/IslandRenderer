#pragma once
#include <memory>
#include <vector>
#include "FilterContainer.h"
#include "../nclgl/Vector3.h"
#include "../nclgl/Matrix4.h"

class Camera;
class ReFrustum;
class ReSceneNode;
class RePointLightComponent;

class PointLightFilter
{
public:
	PointLightFilter(const std::shared_ptr<Camera>& InCamera, const std::shared_ptr<ReFrustum>& InFrustum);
	~PointLightFilter() {}

	void FindPointLights(const std::shared_ptr<ReSceneNode>& InNode);
	void ClearPointLights();

public:
	std::vector<std::shared_ptr<RePointLightComponent>> mPointLights;

protected:
	std::shared_ptr<Camera> mCamera;
	std::shared_ptr<ReFrustum> mFrustum;
};
