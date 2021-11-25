#pragma once
#include <memory>
#include <vector>
#include <string>

class RePrimitive;
class ReMaterialLibrary;

class PrimitiveLibrary
{
public:
	PrimitiveLibrary();
	~PrimitiveLibrary() {};

	void ReadPrimitivesFromDisk();
	std::shared_ptr<RePrimitive> GetPrimitive(unsigned int Index) const;
private:
	std::vector<std::shared_ptr<RePrimitive>> mPrimitives;
};

enum PrimitiveIndex : unsigned int
{
	PRI_COMBINE = 0,
	PRI_SKY_BOX,
	PRI_DIRECT_LIGHT,
	PRI_POINT_LIGHT,
	PRI_HEIGHT_MAP,
	PRI_WATER,
	PRI_CUBE,
	PRI_CUBE_EMISSIVE,
	PRI_FIREFLY,
	PRI_MAX
};