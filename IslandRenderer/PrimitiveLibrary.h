#pragma once
#include <memory>
#include <vector>

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
	PRI_HEIGHT_MAP = 0,
	PRI_MAX
};