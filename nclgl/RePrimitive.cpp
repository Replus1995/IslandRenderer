#include "RePrimitive.h"

RePrimitive::RePrimitive(std::shared_ptr<Mesh> InMesh, ReMaterialPtr InMaterial, bool InTransparent, bool InInstanced)
	: mMesh(InMesh)
	, mMaterial(InMaterial)
	, mBoundingRadius(1.0f)
	, mTransparent(InTransparent)
	, mInstanced(InInstanced)
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
		mMaterial->UpdateRenderParam();
}

void RePrimitive::DrawMesh()
{
	if (mMesh)
		mMesh->Draw();
}
