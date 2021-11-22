#include "SceneGenerator.h"
#include "../nclgl/Camera.h"
#include "../nclgl/ReFrustum.h"
#include "../nclgl/ReSceneNode.h"
#include "../nclgl/RePrimitiveComponent.h"
#include "../nclgl/RePointLightComponent.h"

#include "../nclgl/Mesh.h"
#include "../nclgl/HeightMap.h"

#include "NodeComponent/WaterComponent.h"
#include "Materials/MaterialCollection.h"

#include "GLTFLoader.h"


void SceneGenerator::Build(std::shared_ptr<ReSceneNode> SceneRoot, const PrimitiveLibrary& PrimitiveLib)
{
	ReSceneNodePtr HeightMap_Node(new ReSceneNode());
	SceneRoot->AddChild(HeightMap_Node);
	RePrimitiveComponentPtr HeightMap_Component(new RePrimitiveComponent(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_HEIGHT_MAP)));
	HeightMap_Node->AddComponent(HeightMap_Component);
	std::shared_ptr<HeightMap> HeightMap_Mesh = std::dynamic_pointer_cast<HeightMap>(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_HEIGHT_MAP)->GetMesh());
	//std::shared_ptr<HeightMap> HeightMap_Mesh = std::static_pointer_cast<HeightMap>(HeightMap_Component->GetPrimitive()->GetMesh());
	//HeightMap_Node->SetTransform(Matrix4::Translation(HeightMap_Mesh->GetHeightmapSize() * -0.5f));

	/*
	ReSceneNodePtr TestLight_Node(new ReSceneNode());
	SceneRoot->AddChild(TestLight_Node);
	RePointLightComponentPtr TestLight_Component(new RePointLightComponent(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_POINT_LIGHT), Vector4(1, 1, 1, 1), 500.0f));
	TestLight_Node->AddComponent(TestLight_Component);
	TestLight_Node->SetTransform(Matrix4::Translation(Vector3(200.0f, 250.0f, 200.0f)));

	ReSceneNodePtr TestLight_Node_1(new ReSceneNode());
	SceneRoot->AddChild(TestLight_Node_1);
	RePointLightComponentPtr TestLight_Component_1(new RePointLightComponent(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_POINT_LIGHT), Vector4(0, 1, 0, 1), 500.0f));
	TestLight_Node_1->AddComponent(TestLight_Component_1);
	TestLight_Node_1->SetTransform(Matrix4::Translation(Vector3(-300.0f, 250.0f, -300.0f)));
	*/

	ReSceneNodePtr Water_Node(new ReSceneNode());
	SceneRoot->AddChild(Water_Node);
	RePrimitiveComponentPtr Water_Component(new WaterComponent(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_WATER)));
	Water_Node->AddComponent(Water_Component);
	Water_Node->SetTransform(Matrix4::Translation(Vector3(0, 13, 0)) * Matrix4::Scale(HeightMap_Mesh->GetHeightmapSize() * 0.5f) * Matrix4::Rotation(-90, Vector3(1, 0, 0)));
	
	//Water_Component->SetCostShadow(false);


	//ground//
	ReSceneNodePtr Ground_Node(new ReSceneNode());
	SceneRoot->AddChild(Ground_Node);
	Ground_Node->SetTransform(Matrix4::Translation(Vector3(0, 30, 0)));
	//ground//

	

	ReSceneNodePtr TestCube_Node(new ReSceneNode());
	Ground_Node->AddChild(TestCube_Node);
	RePrimitiveComponentPtr TestCube_Component(new RePrimitiveComponent(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_CUBE)));
	TestCube_Node->AddComponent(TestCube_Component);
	TestCube_Node->SetTransform(Matrix4::Translation(Vector3(200.0f, 200.0f, -200.0f)) * Matrix4::Scale(Vector3(30, 30, 30)));


	GLTFLoader tGLTFLoader;
	tGLTFLoader.LoadFile(MESHDIR"birch_tree.glb");

	std::vector<Matrix4> TreePositions;
	GenTreePositions(TreePositions);
	
	for (const Matrix4& tTreePosition : TreePositions)
	{
		ReSceneNodePtr Tree_Node = GenGLTFNode(&tGLTFLoader);
		Ground_Node->AddChild(Tree_Node);
		Tree_Node->SetTransform(tTreePosition * Matrix4::Scale(Vector3(30, 30, 30)));
	}

	return;
}

std::shared_ptr<ReSceneNode> SceneGenerator::GenGLTFNode(const GLTFLoader* InLoader)
{
	ReSceneNodePtr NewNode(new ReSceneNode());
	for (const RePrimitivePtr& tPrimitive : InLoader->mMeshes[0].mPrimitives)
	{
		RePrimitiveComponentPtr GLTFPriComp(new RePrimitiveComponent(tPrimitive));
		NewNode->AddComponent(GLTFPriComp);
	}
	return NewNode;
}

void SceneGenerator::GenTreePositions(std::vector<Matrix4>& OutMatrices)
{
	OutMatrices.push_back(Matrix4::Translation(Vector3(200.0f, 0.0f, -600.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(220.0f, 0.0f, -650.0f)));
	OutMatrices.push_back(Matrix4::Translation(Vector3(250.0f, 0.0f, -720.0f)));
}
