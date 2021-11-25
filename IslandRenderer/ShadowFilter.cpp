#include "ShadowFilter.h"
#include "../nclgl/ReSceneNode.h"
#include "../nclgl/RePrimitiveComponent.h"


void ShadowFilter::FindPrimitives(const std::shared_ptr<ReSceneNode>& InNode)
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
		if(PrimitiveComponent->CastShadow())
		{
			if (!PrimitiveComponent->IsTransparent())
			{
				mPrimitives_Opaque.push_back(PrimitiveComponent);
			}
		}
	}

	for (auto ChidIter = InNode->GetChildBegin(); ChidIter != InNode->GetChildEnd(); ChidIter++)
	{
		FindPrimitives(*ChidIter);
	}
}

void ShadowFilter::ClearPrimitives()
{
	mPrimitives_Opaque.clear();
}
