#include "RePrimitive.h"

RePrimitive::RePrimitive(std::shared_ptr<Mesh> InMesh, bool InTransparent, ReMaterialPtr InMaterial, ReMaterialParamPtr InMaterialParam)
	: mMesh(InMesh)
	, mTransparent(InTransparent)
	, mBoundingRadius(1.0f)
	, mMaterial(InMaterial)
	, mMaterialParam(InMaterialParam)
{
	//CalculateBoundingRadius();
}

RePrimitive::~RePrimitive()
{
}

void RePrimitive::CalculateBoundingRadius()
{
	if (mMesh)
	{
		mBoundingRadius = mMesh->CalculateMaxRadius();
	}
}

void RePrimitive::UpdateMaterialParams()
{
	if (mMaterial)
		mMaterial->SetMaterialParam(mMaterialParam);
}

void RePrimitive::DrawMesh()
{
	if (mMesh)
		mMesh->Draw();
}
