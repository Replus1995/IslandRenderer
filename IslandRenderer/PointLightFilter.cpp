#include "PointLightFilter.h"
#include "../nclgl/Camera.h"
#include "../nclgl/ReFrustum.h"
#include "../nclgl/ReSceneNode.h"
#include "../nclgl/RePointLightComponent.h"

PointLightFilter::PointLightFilter(const std::shared_ptr<Camera>& InCamera, const std::shared_ptr<ReFrustum>& InFrustum)
	: mCamera(InCamera)
	, mFrustum(InFrustum)
{
}

void PointLightFilter::FindPointLights(const std::shared_ptr<ReSceneNode>& InNode)
{
	std::vector<ReNodeComponentPtr> ComponentList;
	InNode->GetAllComponents(ComponentList,
		[](ReNodeComponentPtr& Component)
	{
		RePointLightComponentPtr PrimitiveComp = std::dynamic_pointer_cast<RePointLightComponent>(Component);
		return PrimitiveComp ? true : false;
	});
	for (ReNodeComponentPtr Component : ComponentList)
	{
		RePointLightComponentPtr PLightComp = std::static_pointer_cast<RePointLightComponent>(Component);
		if (mFrustum->InsideFrustum(PLightComp))
		{
			Vector3 CamDir = PLightComp->GetPosition() - mCamera->GetPosition();
			mPointLights.push_back(PLightComp);
		}
	}

	for (auto ChidIter = InNode->GetChildBegin(); ChidIter != InNode->GetChildEnd(); ChidIter++)
	{
		FindPointLights(*ChidIter);
	}
}

void PointLightFilter::ClearPointLights()
{
	mPointLights.clear();
}
