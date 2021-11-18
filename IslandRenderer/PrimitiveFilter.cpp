#include "PrimitiveFilter.h"
#include <algorithm>
#include "../nclgl/Camera.h"
#include "../nclgl/ReFrustum.h"
#include "../nclgl/ReSceneNode.h"
#include "../nclgl/RePrimitiveComponent.h"

PrimitiveFilter::PrimitiveFilter(const std::shared_ptr<Camera>& InCamera, const std::shared_ptr<ReFrustum>& InFrustum)
	: mCamera(InCamera)
	, mFrustum(InFrustum)
{
}

void PrimitiveFilter::FindPrimitives(const std::shared_ptr<ReSceneNode>& InNode)
{
	std::vector<ReNodeComponentPtr> ComponentList;
	InNode->GetAllComponents(ComponentList,
		[](ReNodeComponentPtr& Component)
	{
		RePrimitiveComponentPtr PrimitiveComp = std::dynamic_pointer_cast<RePrimitiveComponent>(Component);
		return PrimitiveComp ? true : false;
	});
	for (ReNodeComponentPtr Component : ComponentList)
	{
		RePrimitiveComponentPtr PrimitiveComponent = std::static_pointer_cast<RePrimitiveComponent>(Component);
		if (mFrustum->InsideFrustum(PrimitiveComponent))
		{
			Vector3 CamDir = PrimitiveComponent->GetPosition() - mCamera->GetPosition();
			PrimitiveContainer NewContainer;
			NewContainer.Component = PrimitiveComponent;
			NewContainer.Distance = Vector3::Dot(CamDir, CamDir);
			if (PrimitiveComponent->IsTransparent())
			{
				mPrimitives_Transparent.push_back(NewContainer);
			}
			else
			{
				mPrimitives_Opaque.push_back(NewContainer);
			}
		}
	}

	for (auto ChidIter = InNode->GetChildBegin(); ChidIter != InNode->GetChildEnd(); ChidIter++)
	{
		FindPrimitives(*ChidIter);
	}
}

void PrimitiveFilter::SortPrimitives()
{
	std::sort(mPrimitives_Transparent.rbegin(), mPrimitives_Transparent.rend(), PrimitiveContainer::CompareByDistance);
	std::sort(mPrimitives_Opaque.begin(), mPrimitives_Opaque.end(), PrimitiveContainer::CompareByDistance);
}

void PrimitiveFilter::ClearPrimitives()
{
	mPrimitives_Transparent.clear();
	mPrimitives_Opaque.clear();
}
