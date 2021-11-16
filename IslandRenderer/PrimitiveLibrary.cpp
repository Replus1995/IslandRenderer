#include "PrimitiveLibrary.h"
#include "../nclgl/RePrimitive.h"
#include "../nclgl/HeightMap.h"

#include "MaterialCollection.h"

typedef std::shared_ptr<Mesh> MeshPtr;

PrimitiveLibrary::PrimitiveLibrary()
{
}

void PrimitiveLibrary::ReadPrimitivesFromDisk()
{
	mPrimitives.resize(PrimitiveIndex::PRI_MAX);

	///Read HeightMap///
	MeshPtr HeightMap_Mesh(new HeightMap(TEXTUREDIR"noise.png"));
	ReMaterialPtr HeightMap_Mat(new HeightMapMat());
	ReMaterialParamPtr HeightMap_MatParam = HeightMapMatParam::LoadDefault();
	RePrimitivePtr HeightMap_Primitive(new RePrimitive(HeightMap_Mesh, false, HeightMap_Mat, HeightMap_MatParam));
	mPrimitives[PrimitiveIndex::PRI_HEIGHT_MAP] = HeightMap_Primitive;
	///Read HeightMap///

}

std::shared_ptr<RePrimitive> PrimitiveLibrary::GetPrimitive(unsigned int Index) const
{
	if (Index >= mPrimitives.size())
		return nullptr;
	return mPrimitives[Index];
}
