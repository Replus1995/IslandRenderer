#pragma once
#include <map>
#include "ReMaterial.h"

class ReMaterialLibrary
{
public:
	ReMaterialLibrary() {};
	~ReMaterialLibrary();

	void AddMaterial(ReMaterialPtr InMaterial);
	ReMaterialPtr GetMaterial(const std::string& InName);

protected:
	std::map<std::string, unsigned int> mMaterialMap;
	std::vector<ReMaterialPtr> mMaterials;
};
