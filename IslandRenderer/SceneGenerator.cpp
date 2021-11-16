#include "SceneGenerator.h"
#include "../nclgl/Camera.h"
#include "../nclgl/ReFrustum.h"
#include "../nclgl/ReSceneNode.h"
#include "../nclgl/RePrimitiveComponent.h"

#include "MaterialCollection.h"

void SceneGenerator::Build(std::shared_ptr<ReSceneNode> SceneRoot, const PrimitiveLibrary& PrimitiveLib)
{
	ReSceneNodePtr HeightMap_Node(new ReSceneNode());
	SceneRoot->AddChild(HeightMap_Node);
	RePrimitiveComponentPtr HeightMap_Component(new RePrimitiveComponent(PrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_HEIGHT_MAP)));
	HeightMap_Node->AddComponent(HeightMap_Component);
	return;
}