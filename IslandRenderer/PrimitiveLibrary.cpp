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

	MeshPtr Quad_Mesh(Mesh::GenerateQuad());
	MeshPtr Sphere_Mesh(Mesh::LoadFromMeshFile("Sphere.msh"));
	MeshPtr Cube_Mesh(Mesh::LoadFromMeshFile("Cube.msh"));

	//Combine//
	ReMaterialPtr Combine_Mat(new CombinMat());
	RePrimitivePtr Combine_Primitive(new RePrimitive(Quad_Mesh, false, Combine_Mat, nullptr));
	mPrimitives[PrimitiveIndex::PRI_COMBINE] = Combine_Primitive;
	//Combine//

	//SkyBox//
	ReMaterialPtr SkyBox_Mat(new SkyBoxMat());
	ReMaterialParamPtr SkyBox_MatParam = SkyBoxMatParam::LoadDefault();
	RePrimitivePtr SkyBox_Primitive(new RePrimitive(Quad_Mesh, false, SkyBox_Mat, SkyBox_MatParam));
	mPrimitives[PrimitiveIndex::PRI_SKY_BOX] = SkyBox_Primitive;
	//SkyBox//

	//Directional Light//
	ReMaterialPtr DLight_Mat(new DLightMat());
	RePrimitivePtr DLight_Primitive(new RePrimitive(Quad_Mesh, false, DLight_Mat, nullptr));
	mPrimitives[PrimitiveIndex::PRI_DIRECT_LIGHT] = DLight_Primitive;
	//Directional Light//

	///PointLight Sphere///
	ReMaterialPtr PointLight_Mat(new PointLightMat());
	RePrimitivePtr PointLight_Primitive(new RePrimitive(Sphere_Mesh, false, PointLight_Mat, nullptr));
	mPrimitives[PrimitiveIndex::PRI_POINT_LIGHT] = PointLight_Primitive;
	///PointLight Sphere///

	///Read HeightMap///
	std::shared_ptr<HeightMap> HeightMap_Mesh(new HeightMap(TEXTUREDIR"noise.png"));
	ReMaterialPtr HeightMap_Mat(new HeightMapMat());
	ReMaterialParamPtr HeightMap_MatParam = HeightMapMatParam::LoadDefault();
	RePrimitivePtr HeightMap_Primitive(new RePrimitive(HeightMap_Mesh, false, HeightMap_Mat, HeightMap_MatParam));
	HeightMap_Primitive->SetBoundingRadius(HeightMap_Mesh->GetHeightmapSize().Length() / 2.0f);
	mPrimitives[PrimitiveIndex::PRI_HEIGHT_MAP] = HeightMap_Primitive;
	///Read HeightMap///

	//Test Cube//
	ReMaterialPtr Plain_Mat(new PlainMat());
	RePrimitivePtr Cube_Primitive(new RePrimitive(Cube_Mesh, false, Plain_Mat, nullptr));
	Cube_Primitive->SetBoundingRadius(1.0f);
	mPrimitives[PrimitiveIndex::PRI_CUBE] = Cube_Primitive;
	//Test Cube//

}

std::shared_ptr<RePrimitive> PrimitiveLibrary::GetPrimitive(unsigned int Index) const
{
	if (Index >= mPrimitives.size())
		return nullptr;
	return mPrimitives[Index];
}
