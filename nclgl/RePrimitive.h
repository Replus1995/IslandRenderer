#pragma once
#include "Mesh.h"
#include "ReMaterial.h"

class RePrimitive
{
public:
	RePrimitive(std::shared_ptr<Mesh> InMesh, ReMaterialPtr InMaterial, bool InTransparent = false, bool InInstanced = false);
	virtual ~RePrimitive();

	std::shared_ptr<Mesh> GetMesh() { return mMesh; };
	ReMaterialPtr GetMaterial() { return mMaterial; };

	bool IsTransparent() const { return mTransparent; };
	bool IsInstanced() const { return mInstanced; };
	
	void CalculateBoundingRadius();
	float GetBoundingRadius() const { return mBoundingRadius; }
	void SetBoundingRadius(float InRadius) { mBoundingRadius = InRadius; }

	void UpdateMaterialParams();
	void DrawMesh();

protected:
	bool mTransparent;
	bool mInstanced;
	std::shared_ptr<Mesh> mMesh;
	float mBoundingRadius;
	ReMaterialPtr mMaterial;
};

typedef std::shared_ptr<RePrimitive> RePrimitivePtr;