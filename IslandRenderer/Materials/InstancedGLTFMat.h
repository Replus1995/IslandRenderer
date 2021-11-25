#pragma once
#include "GLTFMat.h"

class InstancedGLTFMat : public GLTFMat
{
public:
	InstancedGLTFMat(const std::string& InName)
		: GLTFMat(InName, "InstancedVertex.glsl", "GLTFFragment.glsl")
	{};
	virtual ~InstancedGLTFMat() {};

};