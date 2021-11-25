#pragma once
#include "../../nclgl/ReMaterial.h"

class PointLightMat : public ReMaterial
{
public:
	PointLightMat()
		: ReMaterial("Material_PointLight")
	{
		//LoadShader("PointLightVertex.glsl", "PointLightFragment.glsl");
		LoadShader("PointLightVertex.glsl", "PointLightPbrFragment.glsl");
	};
	~PointLightMat() {};

	virtual void UpdateRenderParam(){};
};


class DLightMat : public ReMaterial
{
public:
	DLightMat()
		: ReMaterial("Material_DirectionalLight")
	{
		//LoadShader("QuadVertex.glsl", "DLightFragment.glsl");
		LoadShader("QuadVertex.glsl", "DLightPbrFragment.glsl");
	};
	~DLightMat() {};

	virtual void UpdateRenderParam() {};
};