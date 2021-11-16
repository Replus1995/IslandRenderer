#include "ReMaterialLibrary.h"

ReMaterialLibrary::~ReMaterialLibrary()
{
}

void ReMaterialLibrary::AddMaterial(ReMaterialPtr InMaterial)
{
	mMaterials.push_back(InMaterial);
	if (!InMaterial->GetName().empty())
	{
		if (mMaterialMap.find(InMaterial->GetName()) != mMaterialMap.end())
		{
			mMaterialMap[InMaterial->GetName()] = mMaterials.size() - 1;
		}
	}

}

ReMaterialPtr ReMaterialLibrary::GetMaterial(const std::string& InName)
{
	if (mMaterialMap.find(InName) != mMaterialMap.end())
	{
		return mMaterials[mMaterialMap[InName]];
	}
	return nullptr;
}
