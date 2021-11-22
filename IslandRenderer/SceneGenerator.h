#pragma once
#include <memory>
#include "PrimitiveLibrary.h"
#include "../nclgl/Matrix4.h"

class ReSceneNode;
class GLTFLoader;

class SceneGenerator
{
public:
	SceneGenerator() {};
	~SceneGenerator() {};

	static void Build(std::shared_ptr<ReSceneNode> SceneRoot, const PrimitiveLibrary& PrimitiveLib);

protected:
	static std::shared_ptr<ReSceneNode> GenGLTFNode(const GLTFLoader* InLoader);
	static void GenTreePositions(std::vector<Matrix4>& OutMatrices);
};