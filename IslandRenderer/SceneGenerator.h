#pragma once
#include <memory>
#include "PrimitiveLibrary.h"

class ReSceneNode;

class SceneGenerator
{
public:
	SceneGenerator() {};
	~SceneGenerator() {};

	static void Build(std::shared_ptr<ReSceneNode> SceneRoot, const PrimitiveLibrary& PrimitiveLib);
};