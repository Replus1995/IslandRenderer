#include "SceneGenerator.h"
#include "../nclgl/Camera.h"
#include "../nclgl/ReFrustum.h"
#include "../nclgl/ReSceneNode.h"
#include "../nclgl/RePrimitiveComponent.h"
#include "../nclgl/RePointLightComponent.h"

#include "../nclgl/HeightMap.h"

#include "MaterialCollection.h"

void SceneGenerator::Build(std::shared_ptr<ReSceneNode> SceneRoot, const PrimitiveLibrary& PrimitiveLib)
{
	ReSceneNodePtr HeightMap_Node(new ReSceneNode());
	SceneRoot->AddChild(HeightMap_Node);
	RePrimitiveComponentPtr HeightMap_Component(new RePrimitiveComponent(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_HEIGHT_MAP)));
	HeightMap_Node->AddComponent(HeightMap_Component);
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

	//ground//
	ReSceneNodePtr Ground_Node(new ReSceneNode());
	SceneRoot->AddChild(Ground_Node);
	Ground_Node->SetTransform(Matrix4::Translation(Vector3(0, 50, 0)));
	//ground//

	ReSceneNodePtr TestCube_Node(new ReSceneNode());
	Ground_Node->AddChild(TestCube_Node);
	RePrimitiveComponentPtr TestCube_Component(new RePrimitiveComponent(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_CUBE)));
	TestCube_Node->AddComponent(TestCube_Component);
	TestCube_Node->SetTransform(Matrix4::Translation(Vector3(200.0f, 200.0f, -200.0f)) * Matrix4::Scale(Vector3(30, 30, 30)));


	return;
}