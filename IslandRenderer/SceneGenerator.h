#pragma once
#include <memory>
#include "PrimitiveLibrary.h"
#include "../nclgl/Matrix4.h"

class Camera;
class ReSceneNode;
class GLTFLoader;

class SceneGenerator
{
public:
	SceneGenerator() {};
	~SceneGenerator() {};

	static void Build(const std::shared_ptr<Camera>& Camera, const std::shared_ptr<ReSceneNode>& SceneRoot, const PrimitiveLibrary& PrimitiveLib);

protected:
	static std::shared_ptr<ReSceneNode> GenGLTFNode(const GLTFLoader* InLoader);
	static void GenTreePositions(std::vector<Matrix4>& OutMatrices);
	static void GenGrassPositions(std::vector<Matrix4>& OutMatrices);

	struct FireFlyParam
	{
		float TimeOffset;
		float Radius;
		Matrix4 Location;
	};
	static void GenFireFlyParams(std::vector<FireFlyParam>& OutParams);
	static std::shared_ptr<ReSceneNode> GenFireFlyNode(const FireFlyParam& InParam, const PrimitiveLibrary& PrimitiveLib);
};