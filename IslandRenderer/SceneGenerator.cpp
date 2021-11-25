#include "SceneGenerator.h"
#include "../nclgl/Camera.h"
#include "../nclgl/ReFrustum.h"
#include "../nclgl/ReSceneNode.h"
#include "../nclgl/RePrimitiveComponent.h"
#include "../nclgl/RePointLightComponent.h"

#include "../nclgl/Mesh.h"
#include "../nclgl/HeightMap.h"

#include "SceneNode/UpDownNode.h"
#include "NodeComponent/WaterComponent.h"
#include "NodeComponent/FireFlyComponent.h"
#include "NodeComponent/ScaleLightComponent.h"
#include "Materials/MaterialCollection.h"

#include "GLTFLoader.h"


void SceneGenerator::Build(const std::shared_ptr<Camera>& Camera, const std::shared_ptr<ReSceneNode>& SceneRoot, const PrimitiveLibrary& PrimitiveLib)
{
	ReSceneNodePtr HeightMap_Node(new ReSceneNode());
	SceneRoot->AddChild(HeightMap_Node);
	RePrimitiveComponentPtr HeightMap_Component(new RePrimitiveComponent(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_HEIGHT_MAP)));
	HeightMap_Node->AddComponent(HeightMap_Component);
	std::shared_ptr<HeightMap> HeightMap_Mesh = std::dynamic_pointer_cast<HeightMap>(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_HEIGHT_MAP)->GetMesh());

	ReSceneNodePtr Water_Node(new ReSceneNode());
	SceneRoot->AddChild(Water_Node);
	RePrimitiveComponentPtr Water_Component(new WaterComponent(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_WATER)));
	Water_Component->SetCostShadow(false);
	Water_Node->AddComponent(Water_Component);
	Water_Node->SetTransform(Matrix4::Translation(Vector3(0, 13, 0)) * Matrix4::Scale(HeightMap_Mesh->GetHeightmapSize() * 0.5f) * Matrix4::Rotation(-90, Vector3(1, 0, 0)));
	


	//ground//
	ReSceneNodePtr Ground_Node(new ReSceneNode());
	SceneRoot->AddChild(Ground_Node);
	Ground_Node->SetTransform(Matrix4::Translation(Vector3(0, 30, 0)));
	//ground//
	

	ReSceneNodePtr CubeOri_Node(new ReSceneNode());
	CubeOri_Node->SetTransform(Matrix4::Translation(Vector3(-80.0f, 60.0f, -680.0f)) * Matrix4::Scale(Vector3(20, 20, 20)));
	Ground_Node->AddChild(CubeOri_Node);
	ReSceneNodePtr CubeAni_Node(new UpDownNode());
	CubeOri_Node->AddChild(CubeAni_Node);
	RePrimitiveComponentPtr Cube_Component(new RePrimitiveComponent(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_CUBE_EMISSIVE)));
	Cube_Component->SetCostShadow(false);
	CubeAni_Node->AddComponent(Cube_Component);
	RePointLightComponentPtr CubeLight_Component(new RePointLightComponent(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_POINT_LIGHT), Vector4(0.1, 0.3, 0.9, 1), 500.0f));
	CubeAni_Node->AddComponent(CubeLight_Component);


	std::unique_ptr<GLTFLoader> tLoader(new GLTFLoader());
	tLoader->LoadFile(MESHDIR"birch_tree.glb", true);

	std::vector<Matrix4> TreePositions;
	GenTreePositions(TreePositions);
	
	for (const Matrix4& tTreePosition : TreePositions)
	{
		ReSceneNodePtr Tree_Node = GenGLTFNode(tLoader.get());
		Ground_Node->AddChild(Tree_Node);
		Tree_Node->SetTransform(tTreePosition * Matrix4::Scale(Vector3(30, 30, 30)));
	}


	tLoader.reset(new GLTFLoader());
	tLoader->LoadFile(MESHDIR"LP_Grass.glb", true);

	std::vector<Matrix4> GrassPositions;
	GenGrassPositions(GrassPositions);

	for (const Matrix4& tGrassPosition : GrassPositions)
	{
		ReSceneNodePtr Grass_Node = GenGLTFNode(tLoader.get());
		Ground_Node->AddChild(Grass_Node);
		Grass_Node->SetTransform(tGrassPosition * Matrix4::Scale(Vector3(30, 30, 30)) * Matrix4::Rotation(15, Vector3(0, 1, 0)));
	}


	tLoader.reset(new GLTFLoader());
	tLoader->LoadFile(MESHDIR"rock2.glb");
	ReSceneNodePtr Rock_Node = GenGLTFNode(tLoader.get());
	Ground_Node->AddChild(Rock_Node);
	Rock_Node->SetTransform(Matrix4::Translation(Vector3(-80.0f, -20.0f, -680.0f)) * Matrix4::Scale(Vector3(50, 50, 50)));
	

	std::vector<FireFlyParam> tFireFlyParams;
	GenFireFlyParams(tFireFlyParams);
	for (const FireFlyParam& tFireFlyParam : tFireFlyParams)
	{
		ReSceneNodePtr FireFly_Node = GenFireFlyNode(tFireFlyParam, PrimitiveLib);
		Ground_Node->AddChild(FireFly_Node);
		FireFly_Node->SetTransform(tFireFlyParam.Location);
	}


	tLoader.reset(new GLTFLoader());
	tLoader->LoadFile(MESHDIR"rock.glb");
	ReSceneNodePtr Rock1_Node = GenGLTFNode(tLoader.get());
	Ground_Node->AddChild(Rock1_Node);
	Rock1_Node->SetTransform(Matrix4::Translation(Vector3(80.0f, 0.0f, 10.0f)) * Matrix4::Scale(Vector3(50, 50, 50)));

	tLoader.reset(new GLTFLoader());
	tLoader->LoadFile(MESHDIR"DamagedHelmet.glb");
	ReSceneNodePtr Helmet_Node = GenGLTFNode(tLoader.get());
	Ground_Node->AddChild(Helmet_Node);
	Helmet_Node->SetTransform(Matrix4::Translation(Vector3(250.0f, 16.0f, -18.0f)) * Matrix4::Scale(Vector3(20, 20, 20)) * Matrix4::Rotation(-60, Vector3(0, 1, 0)) * Matrix4::Rotation(75, Vector3(1, 0, 0)));

	
	return;
}

std::shared_ptr<ReSceneNode> SceneGenerator::GenGLTFNode(const GLTFLoader* InLoader)
{
	ReSceneNodePtr NewNode(new ReSceneNode());
	if (InLoader->mMeshes.size() > 0)
	{
		for (const RePrimitivePtr& tPrimitive : InLoader->mMeshes[0].mPrimitives)
		{
			RePrimitiveComponentPtr GLTFPriComp(new RePrimitiveComponent(tPrimitive));
			NewNode->AddComponent(GLTFPriComp);
		}
	}
	else
	{
		std::cout << "No mesh found in gltf" << std::endl;
	}
	
	return NewNode;
}

void SceneGenerator::GenTreePositions(std::vector<Matrix4>& OutMatrices)
{
	OutMatrices.push_back(Matrix4::Translation(Vector3(200.0f, 0.0f, -600.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(310.0f, 0.0f, -620.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(240.0f, 0.0f, -660.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(240.0f, 0.0f, -760.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(180.0f, 0.0f, -810.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(100.0f, 0.0f, -920.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(-30.0f, 0.0f, -980.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(-100.0f, 0.0f, -975.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(-200.0f, 0.0f, -970.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(-280.0f, 0.0f, -960.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(-350.0f, 0.0f, -980.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(-430.0f, 0.0f, -950.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(-520.0f, 0.0f, -970.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(-530.0f, 0.0f, -900.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(-560.0f, 0.0f, -810.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(-630.0f, 0.0f, -720.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(-610.0f, 0.0f, -620.0f)));
	//OutMatrices.push_back(Matrix4::Translation(Vector3(-610.0f, 0.0f, -620.0f)));
}

void SceneGenerator::GenGrassPositions(std::vector<Matrix4>& OutMatrices)
{
	OutMatrices.push_back(Matrix4::Translation(Vector3(160.0f, -10.0f, -10.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(170.0f, -10.0f, 20.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(180.0f, -10.0f, 0.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(200.0f, -10.0f, 25.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(200.0f, -10.0f, 0.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(220.0f, -10.0f, 10.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(230.0f, -10.0f, -10.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(240.0f, -10.0f, -5.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(250.0f, -10.0f, -20.0f)));

	OutMatrices.push_back(Matrix4::Translation(Vector3(150.0f, -10.0f, -25.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(180.0f, -10.0f, -15.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(210.0f, -10.0f, -25.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(165.0f, -10.0f, -35.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(190.0f, -10.0f, -55.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(225.0f, -10.0f, -65.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(250.0f, -10.0f, -50.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(260.0f, -10.0f, -25.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(275.0f, -10.0f, -55.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(225.0f, -10.0f, -95.0f)));
	/*
	*/
}

void SceneGenerator::GenFireFlyParams(std::vector<FireFlyParam>& OutParams)
{
	OutParams.push_back(FireFlyParam{ 0, 60, Matrix4::Translation(Vector3(230.0f, 18.0f, -50.0f)) });
	OutParams.push_back(FireFlyParam{ 1, 30, Matrix4::Translation(Vector3(200.0f, 15.0f, -70.0f)) });
	OutParams.push_back(FireFlyParam{ 2, 70, Matrix4::Translation(Vector3(170.0f, 21.0f, -90.0f)) });
	OutParams.push_back(FireFlyParam{ 0, 20, Matrix4::Translation(Vector3(195.0f, 17.0f, -75.0f)) });
	OutParams.push_back(FireFlyParam{ 2, 50, Matrix4::Translation(Vector3(165.0f, 14.0f, -50.0f)) });
	OutParams.push_back(FireFlyParam{ 1, 60, Matrix4::Translation(Vector3(150.0f, 15.0f, -40.0f)) });
	OutParams.push_back(FireFlyParam{ 0.5, 80, Matrix4::Translation(Vector3(150.0f, 5.0f, -20.0f)) });
	OutParams.push_back(FireFlyParam{ 1.5, 80, Matrix4::Translation(Vector3(225.0f, 15.0f, -120.0f)) });
}

std::shared_ptr<ReSceneNode> SceneGenerator::GenFireFlyNode(const FireFlyParam& InParam, const PrimitiveLibrary& PrimitiveLib)
{
	ReSceneNodePtr NewNode(new ReSceneNode());
	NewNode->SetTransform(Matrix4::Scale(Vector3(0.5, 0.5, 0.5)));
	RePrimitiveComponentPtr FireFly_Component(new FireFlyComponent(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_FIREFLY), InParam.TimeOffset));
	FireFly_Component->SetCostShadow(false);
	NewNode->AddComponent(FireFly_Component);
	RePointLightComponentPtr FireFlyP_Component(new ScaleLightComponent(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_POINT_LIGHT), Vector4(1, 0.9, 0, 1), InParam.Radius, InParam.TimeOffset));
	NewNode->AddComponent(FireFlyP_Component);
	return NewNode;
}
