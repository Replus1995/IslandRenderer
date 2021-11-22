#pragma once
#include "Mesh.h"
#include "ReMaterial.h"

class RePrimitive
{
public:
	RePrimitive(std::shared_ptr<Mesh> InMesh, bool InTransparent, ReMaterialPtr InMaterial);
	virtual ~RePrimitive();

	std::shared_ptr<Mesh> GetMesh() { return mMesh; };
	ReMaterialPtr GetMaterial() { return mMaterial; };

	bool IsTransparent() const { return mTransparent; };
	
	void CalculateBoundingRadius();
	float GetBoundingRadius() const { return mBoundingRadius; }
	void SetBoundingRadius(float InRadius) { mBoundingRadius = InRadius; }

	void UpdateMaterialParams();
	void DrawMesh();

protected:
	bool mTransparent;
	std::shared_ptr<Mesh> mMesh;
	float mBoundingRadius;
	ReMaterialPtr mMaterial;
};

typedef std::shared_ptr<RePrimitive> RePrimitivePtr;