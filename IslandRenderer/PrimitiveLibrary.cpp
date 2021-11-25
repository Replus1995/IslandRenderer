#include "PrimitiveLibrary.h"

#include "../nclgl/RePrimitive.h"
#include "../nclgl/HeightMap.h"

#include "Materials/MaterialCollection.h"


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
	RePrimitivePtr Combine_Primitive(new RePrimitive(Quad_Mesh, Combine_Mat));
	mPrimitives[PrimitiveIndex::PRI_COMBINE] = Combine_Primitive;
	//Combine//

	//SkyBox//
	std::shared_ptr<SkyBoxMat> SkyBox_Mat(new SkyBoxMat());
	SkyBox_Mat->LoadTextures();
	RePrimitivePtr SkyBox_Primitive(new RePrimitive(Quad_Mesh, SkyBox_Mat));
	mPrimitives[PrimitiveIndex::PRI_SKY_BOX] = SkyBox_Primitive;
	//SkyBox//

	//Directional Light//
	ReMaterialPtr DLight_Mat(new DLightMat());
	RePrimitivePtr DLight_Primitive(new RePrimitive(Quad_Mesh, DLight_Mat));
	mPrimitives[PrimitiveIndex::PRI_DIRECT_LIGHT] = DLight_Primitive;
	//Directional Light//

	///PointLight Sphere///
	ReMaterialPtr PointLight_Mat(new PointLightMat());
	RePrimitivePtr PointLight_Primitive(new RePrimitive(Sphere_Mesh, PointLight_Mat));
	mPrimitives[PrimitiveIndex::PRI_POINT_LIGHT] = PointLight_Primitive;
	///PointLight Sphere///

	///Read HeightMap///
	//std::shared_ptr<HeightMap> HeightMap_Mesh(new HeightMap(TEXTUREDIR"noise.png"));
	std::shared_ptr<HeightMap> HeightMap_Mesh(new HeightMap(TEXTUREDIR"Terrain/Island.png", TEXTUREDIR"Terrain/Island_Colour.png"));
	std::shared_ptr<HeightMapMat> HeightMap_Mat(new HeightMapMat());
	HeightMap_Mat->LoadTextures();
	RePrimitivePtr HeightMap_Primitive(new RePrimitive(HeightMap_Mesh, HeightMap_Mat));
	HeightMap_Primitive->SetBoundingRadius(HeightMap_Mesh->GetHeightmapSize().Length() / 2.0f);
	mPrimitives[PrimitiveIndex::PRI_HEIGHT_MAP] = HeightMap_Primitive;
	///Read HeightMap///

	//Water//
	std::shared_ptr<WaterMat> Water_Mat(new WaterMat());
	Water_Mat->LoadTextures();
	RePrimitivePtr Water_Primitive(new RePrimitive(Quad_Mesh, Water_Mat, true));
	Water_Primitive->SetBoundingRadius(2.0f);
	mPrimitives[PrimitiveIndex::PRI_WATER] = Water_Primitive;
	//Water//

	//Cube//
	ReMaterialPtr Plain_Mat(new PlainMat());
	RePrimitivePtr Cube_Primitive(new RePrimitive(Cube_Mesh, Plain_Mat));
	Cube_Primitive->SetBoundingRadius(1.0f);
	mPrimitives[PrimitiveIndex::PRI_CUBE] = Cube_Primitive;
	//Cube//
	
	//Cube Emissive//
	std::shared_ptr<PlainMat> Emissive_Mat(new PlainMat());
	//Emissive_Mat->mBaseColour = Vector4(0.1, 0.2, 0.8, 0.2);
	Emissive_Mat->mBaseColour = Vector4(0,0,0,1);
	Emissive_Mat->mEmissiveColour = Vector3(0.3, 0.7, 1.0);
	RePrimitivePtr CubeE_Primitive(new RePrimitive(Cube_Mesh, Emissive_Mat));
	CubeE_Primitive->SetBoundingRadius(1.0f);
	mPrimitives[PrimitiveIndex::PRI_CUBE_EMISSIVE] = CubeE_Primitive;
	//Cube Emissive//

	//FireFly//
	std::shared_ptr<PlainMat> FireFly_Mat(new FireFlyMat());
	FireFly_Mat->mBaseColour = Vector4(0, 0, 0, 1);
	FireFly_Mat->mEmissiveColour = Vector3(1.0, 0.9, 0.0);
	FireFly_Mat->bFlatNormal = true;
	RePrimitivePtr FireFly_Primitive(new RePrimitive(Sphere_Mesh, FireFly_Mat));
	FireFly_Primitive->SetBoundingRadius(1.0f);
	mPrimitives[PrimitiveIndex::PRI_FIREFLY] = FireFly_Primitive;
	//FireFly//
	
}

std::shared_ptr<RePrimitive> PrimitiveLibrary::GetPrimitive(unsigned int Index) const
{
	if (Index >= mPrimitives.size())
		return nullptr;
	return mPrimitives[Index];
}
